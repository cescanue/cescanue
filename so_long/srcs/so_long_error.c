/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:15 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/23 21:07:44 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../mlx/includes/so_long_error.h"

void	ft_clearmemlsts(t_data *data)
{
	if (data->awards)
		ft_clearlsti(data->awards);
	if (data->enemy)
		ft_clearlsti(data->enemy);
	if (data->exit)
		ft_clearlsti(data->exit);
	if (data->ground)
		ft_clearlsti(data->ground);
	if (data->ostacles)
		ft_clearlsti(data->ostacles);
	if (data->pup)
		ft_clearlsti(data->pup);
	if (data->pdown)
		ft_clearlsti(data->pdown);
	if (data->pright)
		ft_clearlsti(data->pright);
	if (data->pleft)
		ft_clearlsti(data->pleft);
	ft_clearmemlsts1(data);
}

void	ft_clearmemlsts1(t_data *data)
{
	if (data->gawards)
		ft_clearlstg(data->gawards);
	if (data->gostacles)
		ft_clearlstg(data->gostacles);
	if (data->gground)
		ft_clearlstg(data->gground);
	if (data->gexit)
		ft_clearlstg(data->gexit);
	if (data->gp)
		ft_clearlstg(data->gp);
	if (data->genemies)
		ft_clearlstg(data->genemies);
	if (data->numbers)
		ft_clearlsti(data->numbers);
	if (data->heart)
		ft_clearlsti(data->heart);
}

void	ft_clearmaps(t_data *data)
{
	int	count;

	if (data->map)
	{
		count = 0;
		while (count < data->mapy)
		{
			free(data->map[count]);
			count++;
		}
		free(data->map);
	}
	if (data->mapcheck)
	{
		count = 0;
		while (count < data->mapy)
		{
			free(data->mapcheck[count]);
			count++;
		}
		free(data->mapcheck);
	}
}

void	ft_clearmem(t_data *data)
{
	ft_clearmaps(data);
	ft_clearmemlsts(data);
	if (data->mlx_win)
	{
		mlx_clear_window(data->mlx, data->mlx_win);
		mlx_destroy_window(data->mlx, data->mlx_win);
	}
	if (data->mlx)
	{
		mlx_destroy_image(data->mlx, ((mlx_ptr_t *)data->mlx)->img_list);
		free(((mlx_ptr_t *)data->mlx)->img_list);
		free(data->mlx);
	}
	exit(0);
}

void	ft_error(char *error, t_data *d)
{
	ft_printf("Error\n%s\n", error);
	ft_clearmem(d);
	exit(0);
}
