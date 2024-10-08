/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:40:48 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/14 13:27:32 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_siginfo	*g_info;

void	ft_sendnextbit(void)
{
	unsigned char	bit;

	bit = ((g_info->str[g_info->curchar] >> g_info->curbit) & 1);
	if (!bit)
		kill(g_info->pid, SIGUSR1);
	else
		kill(g_info->pid, SIGUSR2);
	g_info->curbit++;
	if (g_info->curbit == 8)
	{
		g_info->curbit = 0;
		g_info->curchar++;
	}
}

void	ft_cleanexitclient(void)
{
	ft_printf("Message sent.");
	ft_printf("\nMinitalk client has been successfully ");
	ft_printf("completed by cleaning the memory.");
	free(g_info);
	exit(0);
}

void	ft_process_signal_client(int sig, siginfo_t *infoserver, void *context)
{
	(void) context;
	(void) infoserver;
	usleep(175);
	if (sig == SIGINT)
		ft_cleanexitclient();
	if (g_info->curchar < (int) ft_strlen((const char *)g_info->str) + 1)
		ft_sendnextbit();
}

int	main(int argc, char **argv)
{
	struct sigaction	cur;

	ft_printf("Minitalk client cescanue\n");
	if (argc < 3)
	{
		ft_printf("Error in arguments, missing server PID or msg to send.\n");
		return (0);
	}
	g_info = ft_calloc(1, sizeof(t_siginfo));
	g_info->pid = ft_atoi(argv[1]);
	g_info->str = (unsigned char *) argv[2];
	cur.sa_sigaction = ft_process_signal_client;
	sigemptyset(&cur.sa_mask);
	cur.sa_flags = 0;
	ft_sendnextbit();
	while (1)
	{	
		if (g_info->curchar > (int) ft_strlen((const char *)g_info->str))
			ft_cleanexitclient();
		sigaction(SIGUSR1, &cur, NULL);
		sigaction(SIGINT, &cur, NULL);
		pause();
	}
	return (0);
}
