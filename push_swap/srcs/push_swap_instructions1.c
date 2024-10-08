/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_instructions1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 21:45:58 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/28 13:26:03 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_swap(t_list *lst)
{
	int	tmp;

	if (lst && lst->next)
	{
		tmp = lst->nbr;
		lst->nbr = lst->next->nbr;
		lst->next->nbr = tmp;
	}
}

void	ft_rotate(t_list **lst)
{
	t_list	*first;
	t_list	*last;

	first = *lst;
	last = ft_lstlast(*lst);
	if (first && last)
	{
		last->next = first;
		*lst = first->next;
		last->next->next = 0;
	}
}

void	ft_ra(t_data *data)
{
	ft_rotate(data->lsta);
	data->mov++;
	if (data->print)
		ft_putstr_fd("ra\n", 1);
}

void	ft_rb(t_data *data)
{
	ft_rotate(data->lstb);
	data->mov++;
	if (data->print)
		ft_putstr_fd("rb\n", 1);
}

void	ft_rr(t_data *data)
{
	ft_rotate(data->lsta);
	ft_rotate(data->lstb);
	data->mov++;
	if (data->print)
		ft_putstr_fd("rr\n", 1);
}
