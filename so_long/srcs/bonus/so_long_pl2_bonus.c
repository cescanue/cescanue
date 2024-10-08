/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_pl2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:52:23 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/26 13:08:17 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_nextsp(t_gimg *p, t_list *pi)
{
	t_list	*tmp;

	tmp = pi;
	while (tmp && p->img != ((t_img *)tmp->content)->img)
		tmp = tmp->next;
	if (!tmp || !tmp->next)
		p->img = ((t_img *)pi->content)->img;
	else
		p->img = ((t_img *)tmp->next->content)->img;
}

void	ft_move_p2(int key, t_data *d, t_gimg *p)
{
	int	tmp;

	tmp = p->y + p->x;
	if (key == 124 || key == 2)
	{
		ft_nextsp(p, *d->pright);
		p->x += SPEED;
		if (ft_checkcolisionlst(p, *d->gostacles, 10))
			p->x -= SPEED;
	}
	else if (key == 123 || key == 0)
	{
		ft_nextsp(p, *d->pleft);
		p->x -= SPEED;
		if (ft_checkcolisionlst(p, *d->gostacles, 10))
			p->x += SPEED;
	}
	if (p->y + p->x != tmp)
		d->pmv++;
	ft_checkawards(d);
	ft_checkexit(d);
	ft_moveenemies(d);
	ft_animationfire(d);
	ft_printmo(d);
}

void	ft_move_p(int key, t_data *d)
{
	t_gimg	*p;
	int		tmp;

	p = ((t_list *)*d->gp)->content;
	tmp = p->y + p->x;
	if (key == 126 || key == 13)
	{
		ft_nextsp(p, *d->pup);
		p->y -= SPEED;
		if (ft_checkcolisionlst(p, *d->gostacles, 10))
			p->y += SPEED;
	}
	else if (key == 125 || key == 1)
	{
		ft_nextsp(p, *d->pdown);
		p->y += SPEED;
		if (ft_checkcolisionlst(p, *d->gostacles, 10))
			p->y -= SPEED;
	}
	if (p->y + p->x != tmp)
		d->pmv++;
	ft_move_p2(key, d, p);
}

void	ft_move_prelease(int key, t_data *d)
{
	t_gimg	*p;

	p = ((t_list *)*d->gp)->content;
	if (key == 126 || key == 13)
		p->img = ((t_img *)((t_list *)*d->pup)->content)->img;
	else if (key == 125 || key == 1)
		p->img = ((t_img *)((t_list *)*d->pdown)->content)->img;
	else if (key == 124 || key == 2)
		p->img = ((t_img *)((t_list *)*d->pright)->content)->img;
	else if (key == 123 || key == 0)
		p->img = ((t_img *)((t_list *)*d->pleft)->content)->img;
	ft_printallglst(d);
}
