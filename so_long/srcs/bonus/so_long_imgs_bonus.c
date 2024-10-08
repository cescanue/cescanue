/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_imgs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:18:32 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/26 09:33:38 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_putimgtolst(char *file, t_list **lst, t_data *d)
{
	t_img	*img;
	char	tmp[100];

	tmp[0] = 0;
	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		ft_error("allocating memory to load image", d);
	img->img = mlx_xpm_file_to_image(d->mlx, file, &img->w, &img->h);
	if (!img->img)
	{
		ft_strlcat(tmp, "loading image - ", 100);
		ft_strlcat(tmp, file, 100);
		free(img);
		ft_error(tmp, d);
	}
	img->mlx = d->mlx;
	ft_lstadd_back(lst, ft_lstnew(img));
}

void	ft_loadimgs(char *path, t_list **lst, t_data *d)
{
	int		fd;
	char	file[200];
	char	*tmp;

	file[0] = 0;
	ft_strlcat(file, path, 200);
	ft_strlcat(file, "files.txt", 200);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Opening file imgs", d);
	tmp = get_next_line(fd);
	if (tmp && tmp[ft_strlen(tmp) - 1] == '\n')
		tmp[ft_strlen(tmp) - 1] = 0;
	while (tmp)
	{
		file[0] = 0;
		ft_strlcat(file, path, 200);
		ft_strlcat(file, tmp, 200);
		ft_putimgtolst(file, lst, d);
		free(tmp);
		tmp = get_next_line(fd);
		if (tmp && tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = 0;
	}
	close (fd);
}

void	ft_loadallimgs(t_data *data)
{
	ft_loadimgs("imgs/award/", data->awards, data);
	ft_loadimgs("imgs/enemy/", data->enemy, data);
	ft_loadimgs("imgs/exit/", data->exit, data);
	ft_loadimgs("imgs/ground/", data->ground, data);
	ft_loadimgs("imgs/ostacles/", data->ostacles, data);
	ft_loadimgs("imgs/performer/u/", data->pup, data);
	ft_loadimgs("imgs/performer/d/", data->pdown, data);
	ft_loadimgs("imgs/performer/r/", data->pright, data);
	ft_loadimgs("imgs/performer/l/", data->pleft, data);
	ft_loadimgs("imgs/numbers/", data->numbers, data);
	ft_loadimgs("imgs/heart/", data->heart, data);
	ft_loadimgs("imgs/fire/", data->fire, data);
}
