/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:31:53 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/30 17:04:10 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_generateallglst(t_data *d)
{
	ft_generateglst('0', d->gground, *d->ground, d);
	ft_generateglst('1', d->gground, *d->ground, d);
	ft_generateglst('E', d->gground, *d->ground, d);
	ft_generateglst('C', d->gground, *d->ground, d);
	ft_generateglst('P', d->gground, *d->ground, d);
	ft_generateglst('C', d->gawards, *d->awards, d);
	ft_generateglst('1', d->gostacles, *d->ostacles, d);
	ft_generateglst('E', d->gexit, *d->exit, d);
	ft_generateglst('P', d->gp, *d->pdown, d);
}

void	ft_printallglst(t_data *d)
{
	ft_printglst(*d->gground, d);
	ft_printglst(*d->gawards, d);
	ft_printglst(*d->gexit, d);
	ft_printglst(*d->gostacles, d);
	ft_printglst(*d->gp, d);
}

void	ft_game(t_data *d)
{
	ft_generateallglst(d);
	ft_printallglst(d);
	mlx_hook(d->mlx_win, 2, 0, key_hook, d);
	mlx_hook(d->mlx_win, 3, 0, keyrelease_hook, d);
	mlx_hook(d->mlx_win, 17, 0, exit_hook, d);
	mlx_loop(d->mlx);
}
