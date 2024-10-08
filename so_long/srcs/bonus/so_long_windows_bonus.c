/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_windows.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:23:33 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/22 10:19:30 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_init_windows(t_data *d)
{
	d->mlx = mlx_init();
	d->mlx_win = mlx_new_window(d->mlx, (d->mapx * SS),
			(d->mapy * SS) + NUMBERSH + 4, "so_long - cescanue");
	if (!d->mlx || !d->mlx_win)
		ft_error("initializing windows with MLX", d);
}
