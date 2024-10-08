/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_instructions2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:50:14 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/28 13:26:24 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_rrotate(t_list **lst)
{
	t_list	*first;
	t_list	*last;
	t_list	*secondlast;

	first = *lst;
	last = ft_lstlast(*lst);
	secondlast = ft_lstsecondlast(*lst);
	if (first && last && secondlast)
	{
		*lst = last;
		last->next = first;
		secondlast->next = 0;
	}
}

void	ft_rra(t_data *data)
{
	ft_rrotate(data->lsta);
	data->mov++;
	if (data->print)
		ft_putstr_fd("rra\n", 1);
}

void	ft_rrb(t_data *data)
{
	ft_rrotate(data->lstb);
	data->mov++;
	if (data->print)
		ft_putstr_fd("rrb\n", 1);
}

void	ft_rrr(t_data *data)
{
	ft_rrotate(data->lsta);
	ft_rrotate(data->lstb);
	data->mov++;
	if (data->print)
		ft_putstr_fd("rrr\n", 1);
}
