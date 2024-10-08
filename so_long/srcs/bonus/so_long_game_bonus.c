/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:31:53 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/26 09:48:27 by cescanue         ###   ########.fr       */
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
	ft_generafirelst(d);
}

void	ft_printallglst(t_data *d)
{
	ft_printglst(*d->gground, d);
	ft_printglst(*d->gawards, d);
	ft_printglst(*d->gexit, d);
	ft_printglst(*d->genemies, d);
	ft_printglst(*d->gostacles, d);
	ft_printglst(*d->gp, d);
	ft_printglst(*d->gfire, d);
	ft_print_lives(d);
	ft_print_awardsn(d);
}

void	ft_game(t_data *d)
{
	ft_generateallglst(d);
	ft_generateenemies(d);
	ft_printallglst(d);
	ft_printmo(d);
	mlx_hook(d->mlx_win, 2, 0, key_hook, d);
	mlx_hook(d->mlx_win, 3, 0, keyrelease_hook, d);
	mlx_hook(d->mlx_win, 17, 0, exit_hook, d);
	mlx_loop_hook(d->mlx, hook_loop, d);
	mlx_loop(d->mlx);
}
