/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_packet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:48:59 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/22 10:35:41 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	prepare_packet(void *packet, size_t size)
{
	struct icmphdr	*icmp;
	unsigned char	*data;
	size_t			data_size;
	size_t			i;

	icmp = packet;
	ft_memset(packet, 0, size);
	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->un.echo.id = getpid();
	icmp->un.echo.sequence = g_ping.packets_sent;

	if (g_ping.pattern)
	{
		data = (unsigned char *)packet + sizeof(struct icmphdr);
		data_size = size - sizeof(struct icmphdr);
		for (i = 0; i < data_size; i++)
			data[i] = g_ping.data_pattern[i % 16];
	}
	icmp->checksum = 0;
	icmp->checksum = calculate_checksum(packet, size);
}

int	send_packet(void *packet, size_t size)
{
	return (sendto(g_ping.sockfd, packet, size, 0,
			(struct sockaddr *)&g_ping.dest_addr,
			sizeof(g_ping.dest_addr)));
}

void	print_reply(struct timeval *send_time, ssize_t bytes_received,
		struct sockaddr_in *from, struct ip *ip_header,
		struct icmphdr *icmp_reply)
{
	struct timeval	recv_time;
	double			rtt;
	char			ip_str[INET_ADDRSTRLEN];

	gettimeofday(&recv_time, NULL);
	rtt = ((recv_time.tv_sec - send_time->tv_sec) * 1000000.0 +
		   (recv_time.tv_usec - send_time->tv_usec)) / 1000.0;

	if (rtt < g_ping.min_rtt || g_ping.packets_received == 1)
		g_ping.min_rtt = rtt;
	if (rtt > g_ping.max_rtt)
		g_ping.max_rtt = rtt;
	g_ping.total_rtt += rtt;
	g_ping.total_rtt_sq += rtt * rtt;

	inet_ntop(AF_INET, &(from->sin_addr), ip_str, INET_ADDRSTRLEN);
	print_response(ip_str,
		bytes_received - sizeof(struct ip),
		icmp_reply->un.echo.sequence,
		ip_header->ip_ttl,
		rtt);
}

void	handle_icmp_packet(void *packet, size_t size, struct sockaddr_in *from)
{
	struct ip		*ip_header;
	struct icmphdr	*icmp_header;

	if (size < sizeof(struct ip) + sizeof(struct icmphdr))
		return ;
	ip_header = (struct ip *)packet;
	icmp_header = (struct icmphdr *)(packet + (ip_header->ip_hl << 2));
	if (icmp_header->type == ICMP_TIME_EXCEEDED)
		print_icmp_error(icmp_header, from);
}

int	receive_packet(void *packet, size_t size, struct sockaddr_in *from)
{
	socklen_t		from_len;
	ssize_t			ret;
	struct ip		*ip_header;
	struct icmphdr	*icmp_header;
	struct timeval	timeout;
	int				retry_count = 3;

	from_len = sizeof(*from);
	timeout.tv_sec = 0;
	timeout.tv_usec = 100000;  // 100ms timeout

	while (retry_count-- > 0)
	{
		if (setsockopt(g_ping.sockfd, SOL_SOCKET, SO_RCVTIMEO,
				&timeout, sizeof(timeout)) < 0)
		{
			if (g_ping.verbose)
				print_error("setsockopt SO_RCVTIMEO");
			return (-1);
		}

		ret = recvfrom(g_ping.sockfd, packet, size, 0,
				(struct sockaddr *)from, &from_len);
		if (ret >= 0)
			break;
		if (errno != EAGAIN && errno != EWOULDBLOCK)
		{
			if (g_ping.verbose)
				print_error("recvfrom");
			return (-1);
		}
	}

	if (ret < 0)
		return (0);

	if (ret >= (ssize_t)(sizeof(struct ip) + sizeof(struct icmphdr)))
	{
		ip_header = (struct ip *)packet;
		icmp_header = (struct icmphdr *)(packet + (ip_header->ip_hl << 2));
		
		if (icmp_header->type == ICMP_TIME_EXCEEDED)
		{
			struct icmphdr *orig_icmp = (struct icmphdr *)(packet + 
				(ip_header->ip_hl << 2) + 8);  
			char addr_str[INET_ADDRSTRLEN];
			
			inet_ntop(AF_INET, &(from->sin_addr), addr_str, sizeof(addr_str));
			printf("From %s icmp_seq=%d Time to live exceeded\n",
				addr_str, ntohs(orig_icmp->un.echo.sequence) + 1);
			g_ping.errors_received++;
			return (0);
		}
	}
	return (ret);
}