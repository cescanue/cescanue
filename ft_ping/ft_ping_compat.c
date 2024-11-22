/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_compat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:32:43 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/22 10:35:01 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

#ifdef __linux__
void setup_linux_socket(int sockfd) {
    int on = 1;
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_TIMESTAMP, &on, sizeof(on)) < 0) {
        if (g_ping.verbose)
            print_error("setsockopt SO_TIMESTAMP");
    }

    if (setsockopt(sockfd, SOL_IP, IP_RECVERR, &on, sizeof(on)) < 0) {
        if (g_ping.verbose)
            print_error("setsockopt IP_RECVERR");
    }

    if (setsockopt(sockfd, SOL_IP, IP_RECVTTL, &on, sizeof(on)) < 0) {
        if (g_ping.verbose)
            print_error("setsockopt IP_RECVTTL");
    }
}

int handle_linux_error(int sockfd) {
    struct msghdr msg;
    struct sockaddr_in addr;
    struct iovec iov;
    char cbuf[512];
    char buf[512];
    
    ft_memset(&msg, 0, sizeof(msg));
    ft_memset(&addr, 0, sizeof(addr));
    msg.msg_name = &addr;
    msg.msg_namelen = sizeof(addr);
    msg.msg_control = cbuf;
    msg.msg_controllen = sizeof(cbuf);
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    int res = recvmsg(sockfd, &msg, MSG_ERRQUEUE);
    if (res < 0) {
        if (errno != EAGAIN)
            print_error("recvmsg");
        return PING_ERROR;
    }

    return PING_SUCCESS;
}
#endif
