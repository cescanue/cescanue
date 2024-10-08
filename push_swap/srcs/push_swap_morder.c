/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_morder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:38:36 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/30 21:04:06 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_toa_o1_2(t_data *data, t_toa *t)
{
	if (!t->d)
	{	
		ft_pa(data);
		if ((*data->lstb)->index != t->index - (t->dd - 1))
			ft_rr(data);
		else
			ft_ra(data);
		t->index2++;
	}
	else
		ft_rb(data);
}

void	ft_toa_o1(t_data *data, t_toa *t)
{
	int	index;

	t->dd = 10;
	while (t->dd)
	{
		t->d = t->dd;
		if ((*data->lstb)->index == t->index - t->d)
		{
			while (t->d)
			{
				index = t->index - t->d;
				t->f1 = ft_ffirst(index, index, *data->lstb);
				index = t->index - (t->d - 1);
				t->f2 = ft_ffirst(index, index, *data->lstb);
				if (t->f1.pos > t->f2.pos || t->f1.pos == -1
					|| t->f2.pos == -1)
					break ;
				t->d--;
			}
		}
		if (!t->d)
			break ;
		t->dd--;
	}
	ft_toa_o1_2(data, t);
}

void	ft_toa_o2(t_data *data, t_toa *t)
{
	if ((*data->lstb)->index == t->index - 1)
	{
		ft_pa(data);
		ft_ra(data);
		t->index2++;
	}
	else
		ft_rrb(data);
}

void	ft_toa_o3(t_data *data, t_toa *t)
{
	ft_pa(data);
	while (t->index2--)
		ft_rra(data);
}
