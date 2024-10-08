/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_fire_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:37:28 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/26 13:09:33 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_generafirelst(t_data *d)
{
	t_gimg	*tgimg;
	t_point	p;
	t_list	*ilst;
	int		count;

	count = -1;
	while (++count < NFIRES)
	{
		ilst = *d->fire;
		tgimg = ft_calloc(1, sizeof(t_gimg));
		p.y = ft_rand(&d->seed) % d->mapy;
		p.x = ft_rand(&d->seed) % d->mapx;
		if (!tgimg)
			ft_error("Allocating memory for lstenemies", d);
		while (d->map[p.y][p.x] != '1')
		{
			p.y = ft_rand(&d->seed) % d->mapy;
			p.x = ft_rand(&d->seed) % d->mapx;
		}
		tgimg->y = p.y * SS;
		tgimg->x = p.x * SS;
		tgimg->img = ((t_img *)ilst->content)->img;
		ft_lstadd_front(d->gfire, ft_lstnew(tgimg));
	}
}

void	ft_animationfire(t_data *d)
{
	t_list	*tfire;
	t_gimg	*p;

	tfire = *d->gfire;
	while (tfire)
	{
		p = tfire->content;
		ft_nextsp(p, *d->fire);
		tfire = tfire->next;
	}
}

void	ft_checkfire(t_data *d)
{
	t_list	*lst;
	t_gimg	*tgimg;

	lst = *d->gfire;
	while (lst)
	{
		tgimg = lst->content;
		if (ft_checkcolision(((t_list *)*d->gp)->content, tgimg, 5))
		{
			d->lives--;
			if (!d->lives)
			{
				ft_printf("You have died, you have run out of lives...\n");
				ft_clearmem(d);
			}
		}
		lst = lst->next;
	}
}
