/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:32:26 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/22 10:35:47 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void signal_handler(int signo) {
    if (signo == SIGINT || signo == SIGALRM) {
        g_ping.stop_ping = 1;
        if (signo == SIGINT)
            print_statistics();
        cleanup_and_exit(0);
    }
}

void setup_signals(void) {
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    
    if (sigaction(SIGINT, &sa, NULL) < 0) {
        print_error("sigaction SIGINT");
        cleanup_and_exit(1);
    }
    if (sigaction(SIGALRM, &sa, NULL) < 0) {
        print_error("sigaction SIGALRM");
        cleanup_and_exit(1);
    }
}