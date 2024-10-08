/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_enemy2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:09:09 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/26 13:14:46 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_moveenemies1(t_gimg *tgimg, t_data *d)
{
	if (tgimg->d == 0)
	{
		tgimg->y += SPEED / 2;
		if (ft_checkcolisionlst(tgimg, *d->gostacles, 10))
		{
			tgimg->y -= SPEED / 2;
			tgimg->d = ft_rand(&d->seed) % 4;
		}
	}
	else if (tgimg->d == 1)
	{
		tgimg->y -= SPEED / 2 ;
		if (ft_checkcolisionlst(tgimg, *d->gostacles, 10))
		{
			tgimg->y += SPEED / 2;
			tgimg->d = ft_rand(&d->seed) % 4;
		}
	}
}

void	ft_moveenemies2(t_gimg *tgimg, t_data *d)
{
	if (tgimg->d == 2)
	{
		tgimg->x += SPEED / 2;
		if (ft_checkcolisionlst(tgimg, *d->gostacles, 10))
		{
			tgimg->x -= SPEED / 2;
			tgimg->d = ft_rand(&d->seed) % 4;
		}
	}
	else if (tgimg->d == 3)
	{
		tgimg->x -= SPEED / 2;
		if (ft_checkcolisionlst(tgimg, *d->gostacles, 10))
		{
			tgimg->x += SPEED / 2;
			tgimg->d = ft_rand(&d->seed) % 4;
		}
	}
}

void	ft_moveenemies(t_data *d)
{
	t_list	*lst;
	t_gimg	*tgimg;

	lst = *d->genemies;
	while (lst)
	{
		tgimg = lst->content;
		ft_moveenemies1(tgimg, d);
		ft_moveenemies2(tgimg, d);
		if (ft_checkcolision(((t_list *)*d->gp)->content, tgimg, 8))
		{
			d->lives--;
			if (!d->lives)
			{
				ft_printf("You have died, you have run out of lives...\n");
				ft_clearmem(d);
			}
		}
		if (!(ft_rand(&d->seed) % 20))
			tgimg->d = ft_rand(&d->seed) % 4;
		lst = lst->next;
	}
	ft_printallglst(d);
}
