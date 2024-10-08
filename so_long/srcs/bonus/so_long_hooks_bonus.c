/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_hooks_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:29:07 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/26 10:43:36 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <time.h>

int	key_hook(int key, t_data *d)
{
	if (key == 53)
		exit_hook(d);
	if (key == 126 || key == 13 || key == 125 || key == 1 || key == 124
		|| key == 2 || key == 123 || key == 0)
		ft_move_p(key, d);
	return (0);
}

int	keyrelease_hook(int key, t_data *d)
{
	if (key == 126 || key == 13 || key == 125 || key == 1 || key == 124
		|| key == 2 || key == 123 || key == 0)
		ft_move_prelease(key, d);
	return (0);
}

int	exit_hook(t_data *d)
{
	ft_clearmem(d);
	return (0);
}

int	hook_loop(t_data *d)
{
	d->cpuc++;
	if (d->cpuc > TIMEL)
	{
		ft_moveenemies(d);
		ft_animationfire(d);
		ft_checkfire(d);
		d->cpuc = 0;
	}
	return (0);
}
