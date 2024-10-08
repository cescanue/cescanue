/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_instructions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:27:07 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/28 13:25:27 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sa(t_data *data)
{
	ft_swap(*data->lsta);
	data->mov++;
	if (data->print)
		ft_putstr_fd("sa\n", 1);
}

void	ft_sb(t_data *data)
{
	ft_swap(*data->lstb);
	data->mov++;
	if (data->print)
		ft_putstr_fd("sb\n", 1);
}

void	ft_ss(t_data *data)
{
	ft_swap(*data->lsta);
	ft_swap(*data->lstb);
	data->mov++;
	if (data->print)
		ft_putstr_fd("ss\n", 1);
}

void	ft_pa(t_data *data)
{
	t_list	*temp;

	if (*data->lstb)
	{
		temp = *data->lstb;
		ft_lstadd_front(data->lsta, ft_lstnew(temp->nbr, temp->index));
		temp = temp->next;
		free (*data->lstb);
		*data->lstb = temp;
	}
	data->mov++;
	if (data->print)
		ft_putstr_fd("pa\n", 1);
}

void	ft_pb(t_data *data)
{
	t_list	*temp;

	if (*data->lsta)
	{
		temp = *data->lsta;
		ft_lstadd_front(data->lstb, ft_lstnew(temp->nbr, temp->index));
		temp = temp->next;
		free (*data->lsta);
		*data->lsta = temp;
	}
	data->mov++;
	if (data->print)
		ft_putstr_fd("pb\n", 1);
}
