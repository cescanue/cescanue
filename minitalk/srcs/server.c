/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:03:59 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/14 13:27:30 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	ft_decode_msg(int sig, int clientpid, t_list **lst)
{
	t_siginfo	*info;
	int			bit;

	info = ft_get_info(clientpid, lst);
	if (sig == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	info->str[info->curchar] |= bit << info->curbit;
	info->curbit++;
	if (info->curbit == 8)
	{
		if (info->str[info->curchar] == 0)
			ft_printf("%s\n", info->str);
		else
		{
			info->curbit = 0;
			info->curchar++;
		}
	}
	usleep(175);
	kill(clientpid, SIGUSR1);
}

void	ft_process_signal(int sig, siginfo_t *info, void *context)
{
	static t_list	**lst;

	(void) context;
	if (!lst)
		lst = ft_calloc(1, sizeof(t_list *));
	if (sig == SIGINT)
		ft_cleanexit(lst);
	else if (sig == SIGUSR1 || sig == SIGUSR2)
		ft_decode_msg(sig, info->si_pid, lst);
}

int	main(void)
{
	struct sigaction	cur;

	ft_printf("Minitalk Server of cescanue\n");
	ft_printf("Server PID:%d\n", getpid());
	ft_printf("Ready to receive client messages\n");
	cur.sa_sigaction = ft_process_signal;
	sigemptyset(&cur.sa_mask);
	cur.sa_flags = 0;
	while (1)
	{
		sigaction(SIGUSR1, &cur, NULL);
		sigaction(SIGUSR2, &cur, NULL);
		sigaction(SIGINT, &cur, NULL);
		pause();
	}
	return (0);
}
