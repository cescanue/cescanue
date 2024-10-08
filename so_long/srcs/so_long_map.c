/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:13:27 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/19 15:03:38 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_map_count_lines(char *map, t_data *d)
{
	int		fd;
	char	*tmp;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		ft_error("Error opening map file.", d);
	tmp = get_next_line(fd);
	while (tmp)
	{
		d->mapy++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
}

void	ft_loadmap(char *map, t_data *d)
{
	int		fd;
	int		count;

	ft_map_count_lines(map, d);
	if (d->mapy)
	{
		fd = open(map, O_RDONLY);
		if (fd < 0)
			ft_error("Opening map file.", d);
		d->map = ft_calloc(sizeof(char *), d->mapy + 1);
		count = 0;
		d->map[count] = get_next_line(fd);
		while (d->map[count])
		{
			if (d->map[count][ft_strlen(d->map[count]) - 1] == '\n')
				d->map[count][ft_strlen(d->map[count]) - 1] = 0;
			count++;
			d->map[count] = get_next_line(fd);
		}
		close(fd);
		d->mapx = ft_strlen(d->map[0]);
	}
	else
		ft_error("format map error - file empty", d);
}

void	ft_loadmapcheck(char *map, t_data *d)
{
	int		fd;
	int		count;

	if (d->mapy)
	{
		fd = open(map, O_RDONLY);
		if (fd < 0)
			ft_error("Opening map file.", d);
		d->mapcheck = ft_calloc(sizeof(char *), d->mapy + 1);
		count = 0;
		d->mapcheck[count] = get_next_line(fd);
		while (d->map[count])
		{
			if (d->mapcheck[count][ft_strlen(d->mapcheck[count]) - 1] == '\n')
				d->mapcheck[count][ft_strlen(d->mapcheck[count]) - 1] = 0;
			count++;
			d->mapcheck[count] = get_next_line(fd);
		}
		close(fd);
		d->mapx = ft_strlen(d->mapcheck[0]);
	}
	else
		ft_error("format map error - file empty", d);
}
