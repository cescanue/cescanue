/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:48:44 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/26 11:11:24 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_initdata1(t_data *d)
{
	if (!d->awards || !d->enemy || !d->exit || !d->ground || !d->ostacles
		|| !d->pup || !d->pdown || !d->pright || !d->pleft || !d->gawards
		|| !d->gostacles || !d->gground || !d->gexit || !d->gp || !d->numbers
		|| !d->genemies || !d->heart || !d->fire || !d->gfire)
		ft_error("allocating memory for lsts", d);
}

void	ft_initdata(t_data *d)
{
	ft_memset(d, 0, sizeof(t_data));
	d->seed = (unsigned long) &d;
	d->lives = LIVES;
	d->awards = ft_calloc(1, sizeof(t_list *));
	d->enemy = ft_calloc(1, sizeof(t_list *));
	d->exit = ft_calloc(1, sizeof(t_list *));
	d->ground = ft_calloc(1, sizeof(t_list *));
	d->ostacles = ft_calloc(1, sizeof(t_list *));
	d->pup = ft_calloc(1, sizeof(t_list *));
	d->pdown = ft_calloc(1, sizeof(t_list *));
	d->pright = ft_calloc(1, sizeof(t_list *));
	d->pleft = ft_calloc(1, sizeof(t_list *));
	d->heart = ft_calloc(1, sizeof(t_list *));
	d->gawards = ft_calloc(1, sizeof(t_list *));
	d->gostacles = ft_calloc(1, sizeof(t_list *));
	d->gground = ft_calloc(1, sizeof(t_list *));
	d->gexit = ft_calloc(1, sizeof(t_list *));
	d->gp = ft_calloc(1, sizeof(t_list *));
	d->numbers = ft_calloc(1, sizeof(t_list *));
	d->fire = ft_calloc(1, sizeof(t_list *));
	d->genemies = ft_calloc(1, sizeof(t_list *));
	d->gfire = ft_calloc(1, sizeof(t_list *));
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_initdata(&data);
	if (argc == 1)
		ft_error("Missing name of .ber map", &data);
	ft_loadmap(argv[1], &data);
	ft_loadmapcheck(argv[1], &data);
	ft_checkmap(&data);
	ft_init_windows(&data);
	ft_loadallimgs(&data);
	ft_game(&data);
	ft_clearmem(&data);
	return (0);
}
