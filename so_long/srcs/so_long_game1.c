/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:37:30 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/24 19:01:11 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

unsigned int	ft_rand(unsigned long *seed)
{
	*seed = (*seed * 1103515245 + 12345) & 0xFFFFFFFF;
	return ((*seed >> 16) & 0x7FFF);
}

void	ft_generateglst1(t_point p, t_list **lg, t_list *li, t_data *d)
{
	int		r;
	int		count;
	t_gimg	*gimg;

	count = -1;
	r = (ft_rand(&d->seed) % ft_lstsize(li));
	while (++count < r)
		li = li->next;
	gimg = ft_calloc(1, sizeof(t_gimg));
	gimg->y = p.y * SS;
	gimg->x = p.x * SS;
	gimg->img = ((t_img *)li->content)->img;
	ft_lstadd_back(lg, ft_lstnew(gimg));
}

void	ft_generateglst(char type, t_list **lg, t_list *li, t_data *d)
{
	t_point	p;

	p.y = 0;
	p.x = 0;
	while (p.y < d->mapy)
	{
		while (p.x < d->mapx)
		{
			if (d->map[p.y][p.x] == type)
				ft_generateglst1(p, lg, li, d);
			p.x++;
		}
		p.x = 0;
		p.y++;
	}
}

void	ft_printglst(t_list *lg, t_data *d)
{
	t_gimg	*gimg;

	while (lg)
	{
		gimg = lg->content;
		mlx_put_image_to_window(d->mlx, d->mlx_win,
			gimg->img, gimg->x, gimg->y);
		lg = lg->next;
	}
}
