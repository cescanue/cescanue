/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:32:13 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/15 11:32:14 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void cleanup_and_exit(int status) {
    if (g_ping.sockfd != -1)
        close(g_ping.sockfd);
    if (g_ping.data_pattern)
        free(g_ping.data_pattern);
    exit(status);
}

unsigned short calculate_checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

void check_root_privileges(void) {
    if (geteuid() != 0) {
        fprintf(stderr, "ft_ping: This program must be run as root or with CAP_NET_RAW capability.\n");
        fprintf(stderr, "Try running with sudo: 'sudo ft_ping <options> <destination>'\n");
        cleanup_and_exit(1);
    }
}

int parse_pattern(const char *arg) {
    char *endptr;
    long pattern = strtol(arg, &endptr, 16);
    if (*endptr != '\0' || pattern < 0 || pattern > 255) {
        fprintf(stderr, "ft_ping: invalid pattern: %s\n", arg);
        cleanup_and_exit(1);
    }
    return (int)pattern;
}

void *ft_memset(void *b, int c, size_t len) {
    unsigned char *ptr = (unsigned char *)b;
    while (len--)
        *ptr++ = (unsigned char)c;
    return b;
}

char *ft_strdup(const char *s1) {
    size_t len = strlen(s1) + 1;
    char *dup = malloc(len);
    if (!dup)
        return NULL;
    return memcpy(dup, s1, len);
}