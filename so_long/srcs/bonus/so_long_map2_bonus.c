/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:43:46 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/19 15:16:46 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_checkmap(t_data *d)
{
	ft_checkmapwallsud(d);
	ft_checkmapwallsm(d);
	ft_checkmapmin(d);
	ft_checkmapway(d->py, d->px, d);
	if (d->maperror)
		ft_error("Invalid map", d);
	else if (!d->maperrorway)
		ft_error("Invalid map - no exit way", d);
}

void	ft_checkmapway(int y, int x, t_data *d)
{
	if (x < 0 || x >= d->mapx || y < 0
		|| y >= d->mapy || d->mapcheck[y][x] == '1')
		return ;
	if (d->mapcheck[y][x] == 'E')
	{
		d->maperrorway++;
		return ;
	}
	d->mapcheck[y][x] = '1';
	ft_checkmapway(y - 1, x, d);
	ft_checkmapway(y + 1, x, d);
	ft_checkmapway(y, x - 1, d);
	ft_checkmapway(y, x + 1, d);
}
