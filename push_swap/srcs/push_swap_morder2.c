/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_morder2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:41:58 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/02 09:58:01 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_morder_best_performance(t_data *data)
{
	t_data	tmp;
	int		count;
	int		bestmov;
	int		bestsp;

	bestmov = 2147483647;
	count = 20;
	while (count-- > 4)
	{
		tmp = ft_dupdata(data);
		tmp.print = 0;
		tmp.mov = 0;
		tmp.spsize = (110 / 20) * count;
		ft_morder_tob(&tmp);
		ft_morder_toa(&tmp);
		if (tmp.mov < bestmov)
		{
			bestmov = tmp.mov;
			bestsp = tmp.spsize;
		}
		ft_clearmem(&tmp);
	}
	data->spsize = bestsp;
	ft_morder_tob(data);
	ft_morder_toa(data);
}

void	ft_morder_split(t_data *data)
{
	if (data->lstsize < 60)
		data->split = 2;
	else if (data->lstsize <= 100)
		data->split = data->lstsize / 40;
	else if (data->lstsize <= 800)
		data->split = data->lstsize / 60;
	else
			data->split = data->lstsize / 300;
	data->spsize = data->lstsize / data->split;
	data->spsizel = data->spsize;
	data->spsizel += data->lstsize % data->split;
	if (data->lstsize > 1501)
		ft_radix(data);
	else
		ft_morder_best_performance(data);
}

void	ft_morder(t_data *data)
{
	data->lstsize = ft_lstsize(*data->lsta);
	if (!ft_risordered(*data->lsta))
	{
		if (data->lstsize == 2)
			ft_ra(data);
		else if (data->lstsize == 3)
			ft_order3(data);
		else if (data->lstsize == 4)
			ft_order4(data);
		else if (data->lstsize == 5)
			ft_order5(data);
		else
			ft_morder_split(data);
	}
}

t_toa	ft_getdata(t_data *data)
{
	t_toa	t;

	t.index = ft_lstsize(*data->lstb) - 1;
	t.f = ft_ffirst(t.index, t.index, *data->lstb);
	t.l = ft_flast(t.index, t.index, *data->lstb);
	return (t);
}

void	ft_morder_toa(t_data *data)
{
	t_toa	t;

	t = ft_getdata(data);
	while (t.f.pos > -1 || t.l.pos > -1)
	{
		while (t.f.pos > -1 || t.l.pos > -1)
		{
			t = ft_getdata(data);
			t.index2 = 0;
			if (t.f.pos > -1 && t.l.pos > -1
				&& t.f.pos <= (ft_lstsize(*data->lstb) - t.l.pos))
				while ((*data->lstb)->index != t.f.index)
					ft_toa_o1(data, &t);
			else if (t.l.pos > -1)
				while (t.l.pos > -1 && (*data->lstb)->index != t.l.index)
					ft_toa_o2(data, &t);
			if (t.f.pos > -1 && t.l.pos > -1)
				ft_toa_o3(data, &t);
		}
		t = ft_getdata(data);
	}
}
