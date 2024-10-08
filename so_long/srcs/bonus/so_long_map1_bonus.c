/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:12:05 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/19 13:45:03 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_printmap(t_data *d)
{
	int	count;

	count = 0;
	while (count < d->mapy)
	{
		ft_printf("%s\n", d->map[count]);
		count++;
	}
}

void	ft_checkmapmin1(int y, int x, t_data *d)
{
	if (d->map[y][x] != 'C' && d->map[y][x] != '0'
		&& d->map[y][x] != '1' && d->map[y][x] != 'E'
		&& d->map[y][x] != 'P')
		d->maperror++;
	if (d->map[y][x] == 'C')
		d->mapc++;
	else if (d->map[y][x] == 'E')
		d->mape++;
	else if (d->map[y][x] == 'P')
	{
		d->py = y;
		d->px = x;
		d->mapp++;
	}
}

void	ft_checkmapmin(t_data *d)
{
	int	y;
	int	x;

	y = 0;
	while (y < d->mapy)
	{
		x = 0;
		while (x < d->mapx)
		{
			ft_checkmapmin1(y, x, d);
			x++;
		}
		y++;
	}
	if (d->mape > 1 || d->mapp > 1 || d->mapc == 0)
		d->maperror++;
}

void	ft_checkmapwallsud(t_data *d)
{
	int	count;

	count = 0;
	while (count < d->mapx)
	{
		if (d->map[0][count] != '1')
			d->maperror++;
		count++;
	}
	count = 0;
	while (count < d->mapx)
	{
		if (d->map[d->mapy - 1][count] != '1')
			d->maperror++;
		count++;
	}
}

void	ft_checkmapwallsm(t_data *d)
{
	int	count;

	count = 1;
	while (count < d->mapy - 1)
	{
		if (d->map[count][0] != '1' || d->map[count][d->mapx - 1] != '1')
			d->maperror++;
		count++;
	}
}
