/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_morder1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:14:47 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/28 11:08:55 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_order3(t_data *data)
{
	int		nbrs[3];
	t_list	*lsta;

	lsta = *data->lsta;
	nbrs[0] = lsta->index;
	nbrs[1] = lsta->next->index;
	nbrs[2] = lsta->next->next->index;
	if (nbrs[0] > nbrs[1] && nbrs[1] < nbrs[2] && nbrs[2] > nbrs[0])
		ft_sa(data);
	else if (nbrs[0] > nbrs[1] && nbrs[1] > nbrs[2] && nbrs[2] < nbrs[0])
	{
		ft_sa(data);
		ft_rra(data);
	}
	else if (nbrs[0] > nbrs[1] && nbrs[1] < nbrs[2] && nbrs[2] < nbrs[0])
		ft_ra(data);
	else if (nbrs[0] < nbrs[1] && nbrs[1] > nbrs[2] && nbrs[2] > nbrs[0])
	{
		ft_sa(data);
		ft_ra(data);
	}
	else if (nbrs[0] < nbrs[1] && nbrs[1] > nbrs[2] && nbrs[2] < nbrs[0])
		ft_rra(data);
}

int	ft_findpos(int index, t_list *lst)
{	
	int	pos;

	pos = -1;
	while (lst && lst->index != index)
	{
		pos++;
		lst = lst->next;
	}
	if (pos != -1)
		pos++;
	return (pos);
}

int	ft_findmin(t_list *lst)
{
	int	min;

	min = 2147483647;
	while (lst)
	{
		if (lst->index < min)
			min = lst->index;
		lst = lst->next;
	}
	return (min);
}

void	ft_order4(t_data *data)
{
	int	min;

	min = ft_findmin(*data->lsta);
	if (ft_findpos(min, *data->lsta) < data->lstsize / 2)
		while ((*data->lsta)->index != min)
			ft_ra(data);
	else
		while ((*data->lsta)->index != min)
			ft_rra(data);
	ft_pb(data);
	ft_order3(data);
	ft_pa(data);
}

void	ft_order5(t_data *data)
{
	int	i5;
	int	min;

	i5 = 0;
	while (i5 != 2)
	{
		min = ft_findmin(*data->lsta);
		if (ft_findpos(min, *data->lsta) < data->lstsize / 2)
			while ((*data->lsta)->index != min)
				ft_ra(data);
		else
			while ((*data->lsta)->index != min)
				ft_rra(data);
		i5++;
		ft_pb(data);
	}
	ft_order3(data);
	ft_pa(data);
	ft_pa(data);
}
