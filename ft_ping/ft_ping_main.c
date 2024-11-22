/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:48:55 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/22 10:31:20 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_ping  g_ping = {0};

static void    init_ping_struct(void)
{
    g_ping.sockfd = -1;
    g_ping.min_rtt = __DBL_MAX__;
    g_ping.ttl = DEFAULT_TTL;
    g_ping.timeout = DEFAULT_TIMEOUT;
    g_ping.interval = DEFAULT_INTERVAL;
    g_ping.packet_size = DEFAULT_PACKET_SIZE;
    g_ping.stop_ping = 0;
    g_ping.packets_sent = 0;
    g_ping.packets_received = 0;
    g_ping.errors_received = 0;
    g_ping.total_rtt = 0;
    g_ping.total_rtt_sq = 0;
    g_ping.max_rtt = 0;
    g_ping.data_pattern = NULL;
    g_ping.target = NULL;
    g_ping.quiet = 0;
    g_ping.waiting = 0;
    g_ping.flood = 0;
    g_ping.verbose = 0;
    g_ping.numeric = 0;
    g_ping.routing = 0;
    g_ping.pattern = 0;
    g_ping.deadline = 0;
    g_ping.count = 0;
    g_ping.is_domain = 0;
}

static void	ping_loop(void)
{
	char				packet[g_ping.packet_size];
	char				recv_packet[g_ping.packet_size + sizeof(struct iphdr)];
	struct timeval		send_time;
	struct sockaddr_in	recv_addr;
	ssize_t				bytes_received;
	struct ip			*ip_header;
	struct icmphdr		*icmp_reply;
	size_t				sent;

	sent = 0;
	if (g_ping.pattern)
    	printf("PATTERN: 0x%02x\n", g_ping.pattern);
	print_ping_header();
	
	while (!g_ping.stop_ping && (g_ping.count == 0 || sent < g_ping.count))
	{
		prepare_packet(packet, g_ping.packet_size);
		gettimeofday(&send_time, NULL);
		if (send_packet(packet, g_ping.packet_size) <= 0)
		{
			if (g_ping.verbose)
				print_error("sendto");
			continue ;
		}
		if (sent == 0 || sent == 1) 
            gettimeofday(&g_ping.start_time, NULL);
		g_ping.packets_sent++;
		sent++;

		bytes_received = receive_packet(recv_packet, sizeof(recv_packet),
				&recv_addr);
		if (bytes_received > 0)
		{
			ip_header = (struct ip *)recv_packet;
			icmp_reply = (struct icmphdr *)(recv_packet
					+ (ip_header->ip_hl << 2));
			if (icmp_reply->type == ICMP_ECHOREPLY
				&& icmp_reply->un.echo.id == getpid())
			{
				g_ping.packets_received++;
				print_reply(&send_time, bytes_received, &recv_addr,
					ip_header, icmp_reply);
			}
			else if (g_ping.verbose)
				printf("Received ICMP packet with type: %d\n", icmp_reply->type);
		}
		if (!g_ping.flood)
			usleep(g_ping.interval);
	}
	print_statistics();
}

static void	parse_arguments(int argc, char *argv[])
{
	int				opt;
	struct option	long_options[] = {
		{"ttl", required_argument, 0, 't'},
		{"help", no_argument, 0, '?'},
		{0, 0, 0, 0}
	};

	while ((opt = getopt_long(argc, argv, "c:vfnw:W:p:rs:t:?",
				long_options, NULL)) != -1)
	{
		switch (opt)
		{
			case 'c':
				g_ping.count = atoi(optarg);
				if (g_ping.count <= 0)
				{
					fprintf(stderr, "ft_ping: invalid count: %s\n", optarg);
					cleanup_and_exit(1);
				}
				break ;
			case 'v':
				g_ping.verbose = 1;
				break ;
			case 'f':
				g_ping.flood = 1;
				g_ping.interval = 0;
				break ;
			case 'n':
				g_ping.numeric = 1;
				break ;
			case 'w':
				g_ping.deadline = atoi(optarg);
				if (g_ping.deadline <= 0)
				{
					fprintf(stderr, "ft_ping: invalid deadline: %s\n", optarg);
					cleanup_and_exit(1);
				}
				if (g_ping.deadline > 0)
					alarm(g_ping.deadline);
				break ;
			case 'W':
				g_ping.timeout = atoi(optarg);
				if (g_ping.timeout <= 0)
				{
					fprintf(stderr, "ft_ping: invalid timeout: %s\n", optarg);
					cleanup_and_exit(1);
				}
				break ;
			case 'p':
				if (!g_ping.data_pattern)
				{
					g_ping.data_pattern = malloc(16);
					if (!g_ping.data_pattern)
					{
						perror("malloc");
						cleanup_and_exit(1);
					}
				}
				g_ping.pattern = parse_pattern(optarg);
				for (int i = 0; i < 16; i++)
					g_ping.data_pattern[i] = g_ping.pattern;
				break ;
			case 'r':
				g_ping.routing = 1;
				break ;
			case 's':
				g_ping.packet_size = atoi(optarg);
				if (g_ping.packet_size < MIN_PACKET_SIZE
					|| g_ping.packet_size > MAX_PACKET_SIZE)
				{
					fprintf(stderr, "ft_ping: invalid packet size: %s\n", optarg);
					cleanup_and_exit(1);
				}
				break ;
			case 't':
				g_ping.ttl = atoi(optarg);
				if (g_ping.ttl <= 0 || g_ping.ttl > 255)
				{
					fprintf(stderr, "ft_ping: invalid TTL: %s\n", optarg);
					cleanup_and_exit(1);
				}
				break ;
			case '?':
				print_usage();
				break ;
			default:
				print_usage();
		}
	}
	if (optind >= argc)
	{
		fprintf(stderr, "ft_ping: missing host operand\n");
		print_usage();
	}
	g_ping.target = argv[optind];
}

int	main(int argc, char *argv[])
{
	init_ping_struct();
	check_root_privileges();
	setup_signals();
	parse_arguments(argc, argv);
	if (create_socket() < 0)
		cleanup_and_exit(1);
	ping_loop();
	return (0);
}