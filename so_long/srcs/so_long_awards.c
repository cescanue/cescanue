/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_awards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:49:12 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/24 18:57:44 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_checkawards(t_data *d)
{
	t_list	*t;

	t = ft_checkcolisionlst(((t_list *)*d->gp)->content, *d->gawards, 2);
	if (t)
	{
		ft_lstdelonem(d->gawards, t, ft_dellstg);
		d->tawards++;
	}
}

void	ft_checkexit(t_data *d)
{
	t_list	*t;

	t = ft_checkcolisionlst(((t_list *)*d->gp)->content, *d->gexit, 3);
	if (t && !ft_lstsize(*d->gawards))
	{
		ft_printf("You win, you have collected all the");
		ft_printf(" treasures and you have reached the exit.\n");
		ft_clearmem(d);
	}
}
