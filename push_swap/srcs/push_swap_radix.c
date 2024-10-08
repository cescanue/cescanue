/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_radix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:20:40 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/03 14:48:10 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_generateindex(t_data	*data)
{
	t_list	*lst;
	t_list	*lst1;
	int		index;
	int		lstsize;
	int		min;

	index = 0;
	lstsize = ft_lstsize(*data->lsta);
	while (index != lstsize)
	{
		min = 2147483647;
		lst1 = 0;
		lst = *data->lsta;
		while (lst)
		{
			if (lst->index == -1 && lst->nbr <= min)
			{
				lst1 = lst;
				min = lst->nbr;
			}
			lst = lst->next;
		}
		lst1->index = index;
		index++;
	}
}

int	ft_rgetmaxbit(t_list	*lst)
{
	int	maxbit;
	int	maxindex;

	maxindex = -2147483648;
	maxbit = 0;
	while (lst)
	{
		if (lst->index > maxindex)
			maxindex = lst->index;
		lst = lst->next;
	}
	while (maxindex >> maxbit)
		maxbit++;
	return (maxbit);
}

void	ft_radix(t_data	*data)
{
	int		maxbit;
	int		count;
	int		count1;
	int		lstasize;
	t_list	*tlst;

	maxbit = ft_rgetmaxbit(*data->lsta);
	count = 0;
	lstasize = ft_lstsize(*data->lsta);
	while (!ft_risordered(*data->lsta) && count < maxbit)
	{
		count1 = 0;
		while (!ft_risordered(*data->lsta) && (count1 < lstasize))
		{
			tlst = *data->lsta;
			if ((tlst->index >> count) & 1)
				ft_ra(data);
			else
				ft_pb(data);
			count1++;
		}
		while (ft_lstsize(*data->lstb))
			ft_pa(data);
		count++;
	}
}

int	ft_risordered(t_list *lst)
{
	int	cur;

	cur = -2147483648;
	while (lst)
	{
		if (lst->nbr < cur)
			return (0);
		cur = lst->nbr;
		lst = lst->next;
	}
	return (1);
}
