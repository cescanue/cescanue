/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_socket.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:49:11 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/21 11:49:12 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void    set_socket_options(void)
{
    int             opt;
    struct timeval  tv_out;

    opt = 1;
    tv_out.tv_sec = g_ping.timeout;
    tv_out.tv_usec = 0;
    if (setsockopt(g_ping.sockfd, SOL_SOCKET, SO_RCVTIMEO,
            &tv_out, sizeof(tv_out)) < 0)
    {
        print_error("setsockopt SO_RCVTIMEO");
        cleanup_and_exit(1);
    }
    if (setsockopt(g_ping.sockfd, IPPROTO_IP, IP_TTL,
            &g_ping.ttl, sizeof(g_ping.ttl)) < 0)
    {
        print_error("setsockopt IP_TTL");
        cleanup_and_exit(1);
    }
    if (setsockopt(g_ping.sockfd, IPPROTO_IP, IP_RECVERR, &opt, sizeof(opt)) < 0)
    {
        print_error("setsockopt IP_RECVERR");
        cleanup_and_exit(1);
    }
    if (g_ping.verbose)
        printf("ping: sock4.fd: %d (socktype: SOCK_RAW), sock6.fd: 4 "
            "(socktype: SOCK_RAW), hints.ai_family: AF_UNSPEC\n",
            g_ping.sockfd);
}

static void    resolve_target(void)
{
    struct hostent  *host_entity;
    struct in_addr  addr;
    char           *ip_str;

    if (inet_aton(g_ping.target, &addr) != 0)
    {
        g_ping.is_domain = 0;  // Es una IP
        host_entity = gethostbyaddr(&addr, sizeof(addr), AF_INET);
        if (g_ping.verbose)
        {
            ip_str = ft_strdup(g_ping.target);
            printf("ai->ai_family: AF_INET, ai->ai_canonname: '%s'\n", ip_str);
            free(ip_str);
        }
    }
    else
    {
        g_ping.is_domain = 1;  // Es un dominio
        host_entity = gethostbyname(g_ping.target);
        if (!host_entity)
        {
            print_host_error(g_ping.target);
            cleanup_and_exit(1);
        }
        if (g_ping.verbose)
        {
            ip_str = inet_ntoa(*(struct in_addr *)host_entity->h_addr);
            printf("ai->ai_family: AF_INET, ai->ai_canonname: '%s'\n", ip_str);
        }
    }
    ft_memset(&g_ping.dest_addr, 0, sizeof(g_ping.dest_addr));
    if (host_entity)
    {
        g_ping.dest_addr.sin_family = host_entity->h_addrtype;
        g_ping.dest_addr.sin_addr.s_addr = *(long *)host_entity->h_addr;
    }
    else
    {
        g_ping.dest_addr.sin_family = AF_INET;
        g_ping.dest_addr.sin_addr = addr;
    }
}

int create_socket(void)
{
    int sockfd;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0)
    {
        if (errno == EPERM)
            fprintf(stderr, "ping: socket: Operation not permitted\n");
        else
            print_error("socket");
        return (-1);
    }
    g_ping.sockfd = sockfd;
    set_socket_options();
    resolve_target();
    return (sockfd);
}