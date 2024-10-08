/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_enemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:29:18 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/23 11:27:17 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_countblanks(t_data *d)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	x = 0;
	count = 0;
	while (y < d->mapy)
	{
		while (x < d->mapx)
		{
			if (d->map[y][x] == '0')
				count++;
			x++;
		}
		x = 0;
		y++;
	}
	return (count);
}

void	ft_putenemylst(t_list *ilst, t_data *d)
{
	t_gimg	*tgimg;
	t_point	p;
	int		r;
	int		count;

	tgimg = ft_calloc(1, sizeof(t_gimg));
	p.y = 0;
	p.x = 0;
	if (!tgimg)
		ft_error("Allocating memory for lstenemies", d);
	while (d->map[p.y][p.x] != '0')
	{
		p.y = ft_rand(&d->seed) % d->mapy;
		p.x = ft_rand(&d->seed) % d->mapx;
	}
	r = (ft_rand(&d->seed) % ft_lstsize(ilst));
	count = -1;
	while (++count < r)
		ilst = ilst->next;
	tgimg->y = p.y * SS;
	tgimg->x = p.x * SS;
	tgimg->d = ft_rand(&d->seed) % 4;
	tgimg->img = ((t_img *)ilst->content)->img;
	ft_lstadd_front(d->genemies, ft_lstnew(tgimg));
}

void	ft_generateenemies(t_data *d)
{
	int	nenemies;
	int	count;

	count = 0;
	nenemies = ft_countblanks(d) / NENEMIES;
	if (!nenemies)
		nenemies++;
	d->lives = LIVES * nenemies;
	d->tlives = d->lives;
	while (count < nenemies)
	{
		ft_putenemylst(*d->enemy, d);
		count++;
	}
}
