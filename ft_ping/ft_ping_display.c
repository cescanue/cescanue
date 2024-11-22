/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:48:51 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/22 10:35:12 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_usage(void)
{
	printf("Usage\n");
	printf("  ping [options] <destination>\n\n");
	printf("Options:\n");
	printf("  <destination>      dns name or ip address\n");
	printf("  -c <count>         stop after <count> replies\n");
	printf("  -v                 verbose output\n");
	printf("  -f                 flood ping\n");
	printf("  -n                 numeric output only\n");
	printf("  -w                 deadline in seconds\n");
	printf("  -W                 timeout in seconds\n");
	printf("  -p                 pattern to fill packet\n");
	printf("  -r                 bypass routing tables\n");
	printf("  -s                 packet size\n");
	printf("  -t                 time to live\n");
	printf("  -?                 this help message\n");
	exit(0);
}

void	print_error(const char *msg)
{
	fprintf(stderr, "ping: %s: %s\n", msg, strerror(errno));
}

void	print_host_error(const char *hostname)
{
	fprintf(stderr, "ping: %s: Nombre o servicio desconocido\n", hostname);
}

void	print_ping_header(void)
{
	char	ip_str[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &(g_ping.dest_addr.sin_addr), ip_str, INET_ADDRSTRLEN);
	printf("PING %s (%s) 56(84) bytes of data.\n",
		g_ping.target, ip_str);
}

void    print_response(const char *target, __attribute__((unused)) size_t bytes,
        uint16_t seq, uint8_t ttl, double rtt)
{
    char                *display_target;
    struct sockaddr_in  addr;
    struct hostent      *host;

    if (g_ping.numeric)
    {
        display_target = ft_strdup(target);
    }
    else
    {
        addr.sin_family = AF_INET;
        inet_pton(AF_INET, target, &addr.sin_addr);
        host = gethostbyaddr(&addr.sin_addr, sizeof(addr.sin_addr), AF_INET);
        if (host && g_ping.is_domain)  
        {
            char ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &addr.sin_addr, ip_str, sizeof(ip_str));
            display_target = malloc(strlen(host->h_name) + strlen(ip_str) + 4);
            if (display_target)
                sprintf(display_target, "%s (%s)", host->h_name, ip_str);
            else
                display_target = ft_strdup(target);
        }
        else
            display_target = ft_strdup(target);
    }
	if (g_ping.flood)
    	printf(".");
    else if (g_ping.verbose)
        printf("64 bytes from %s: icmp_seq=%d ident=%d ttl=%d time=%.1f ms\n",
            display_target, seq + 1, getpid() & 0xFFFF, ttl, rtt);
    else
        printf("64 bytes from %s: icmp_seq=%d ttl=%d time=%.1f ms\n",
            display_target, seq + 1, ttl, rtt);

    free(display_target);
    fflush(stdout);
}

void    print_statistics(void)
{
    double          loss_percent;
    double          time_ms;
    double          avg;
    double          mdev;
    struct timeval  end_time;

    gettimeofday(&end_time, NULL);
    time_ms = ((end_time.tv_sec - g_ping.start_time.tv_sec) * 1000.0) +
              ((end_time.tv_usec - g_ping.start_time.tv_usec) / 1000.0);

    loss_percent = 0.0;
    if (g_ping.packets_sent > 0)
        loss_percent = ((double)(g_ping.packets_sent - g_ping.packets_received)
                / g_ping.packets_sent) * 100.0;

    printf("\n--- %s ping statistics ---\n", g_ping.target);
    printf("%zu packets transmitted, %zu received",
        g_ping.packets_sent, g_ping.packets_received);
    if (g_ping.errors_received > 0)
        printf(", +%zu errors", g_ping.errors_received);
    printf(", %d%% packet loss, time %.0fms\n",
        (int)loss_percent, time_ms);

    if (g_ping.packets_received > 0)
    {
        avg = g_ping.total_rtt / g_ping.packets_received;
        mdev = 0;
        if (g_ping.packets_received > 1)
        {
            double variance = (g_ping.total_rtt_sq / g_ping.packets_received)
                - (avg * avg);
            mdev = sqrt(variance);
        }
        printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
            g_ping.min_rtt, avg, g_ping.max_rtt, mdev);
    }
}

void	print_verbose(const char *msg)
{
	if (g_ping.verbose)
	{
		printf("%s\n", msg);
		fflush(stdout);
	}
}

void	print_icmp_error(struct icmphdr *icmp_header, struct sockaddr_in *from)
{
	char	addr_str[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &(from->sin_addr), addr_str, sizeof(addr_str));
	if (icmp_header->type == ICMP_TIME_EXCEEDED)
	{
		printf("From %s icmp_seq=%zu Time to live exceeded\n",
			addr_str, g_ping.packets_sent - 1);
		g_ping.errors_received++;
	}
}