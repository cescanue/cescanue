/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_morder3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:18:24 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/28 21:25:47 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_find	ft_ffirst(int start, int end, t_list *lst)
{
	t_find	find;

	find.pos = 0;
	while (lst)
	{
		if (lst->index >= start && lst->index <= end)
		{
			find.index = lst->index;
			return (find);
		}
		find.pos++;
		lst = lst->next;
	}
	find.pos = -1;
	return (find);
}

t_find	ft_flast(int start, int end, t_list *lst)
{
	t_find	find;
	int		pos;

	find.pos = 0;
	pos = 0;
	find.index = -1;
	while (lst)
	{
		if (lst->index >= start && lst->index <= end)
		{
			find.index = lst->index;
			find.pos = pos;
		}
		pos++;
		lst = lst->next;
	}
	if (find.index == -1)
		find.pos = -1;
	return (find);
}

int	ft_max(t_data *data)
{
	int	max;

	max = data->spsize * (data->maxc + 1);
	if (max >= data->lstsize - 6)
		max = data->lstsize - 6;
	return (max);
}

void	ft_morder_tob(t_data *d)
{
	t_find	f;

	d->maxc = 0;
	d->maxlstsize = ft_lstsize(*d->lstb);
	f = ft_ffirst(d->spsize * d->maxc, ft_max(d), *d->lsta);
	while (f.pos > -1)
	{
		while (f.pos > -1)
		{
			f = ft_ffirst(d->spsize * d->maxc, ft_max(d), *d->lsta);
			while (f.pos > -1 && (*d->lsta)->index != f.index)
				ft_ra(d);
			if (f.pos > -1)
			{
				ft_pb(d);
				if ((*d->lstb)->index < (d->spsize / 2) + (d->spsize * d->maxc))
					ft_rb(d);
			}
		}
		d->maxc++;
		f = ft_ffirst(d->spsize * d->maxc, ft_max(d), *d->lsta);
	}
	ft_order5(d);
}
