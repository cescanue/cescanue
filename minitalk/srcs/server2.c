/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:25:02 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/12 18:40:28 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	ft_lstfindpid(void *content, int pid)
{
	t_siginfo	*tmp;

	tmp = content;
	if (tmp->pid == pid)
		return (1);
	return (0);
}

void	ft_free_siginfo(void *info)
{
	t_siginfo	*tmp;

	tmp = info;
	free(tmp->str);
	free(tmp);
}

void	ft_cleanexit(t_list **lst)
{
	ft_lstclear(lst, ft_free_siginfo);
	ft_printf("\nMinitalk server of cescanue.\nSuccessfully releasing the used");
	ft_printf(" memory. \nTermination of the process requested by the user");
	ft_printf(" with the option control-C to stop the program.\n");
	exit(0);
}

t_siginfo	*ft_get_info(int clientpid, t_list **lst)
{
	t_siginfo	*info;

	info = ft_lstfindcontent(*lst, ft_lstfindpid, clientpid);
	if (!info)
	{
		info = ft_calloc (1, sizeof(t_siginfo));
		info->pid = clientpid;
		info->curchar = 0;
		info->curbit = 0;
		info->str = ft_calloc(STRSIZE, sizeof(char));
		ft_lstadd_front(lst, ft_lstnew(info));
	}
	return (info);
}
