/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:07:20 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/13 21:23:21 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include "../ft_printf/libft/includes/libft.h"
# include "../ft_printf/includes/ft_printf.h"

# define STRSIZE 20000

typedef struct siginfo
{
	int				pid;
	int				curbit;
	int				curchar;
	unsigned char	*str;

}	t_siginfo;

int			ft_lstfindpid(void *content, int pid);
void		ft_free_siginfo(void *info);
void		ft_cleanexit(t_list **lst);
t_siginfo	*ft_get_info(int clientpid, t_list **lst);
void		ft_decode_msg(int sig, int clientpid, t_list **lst);
void		ft_process_signal(int sig, siginfo_t *info, void *context);

#endif