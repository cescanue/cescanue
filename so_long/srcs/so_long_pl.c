/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_pl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:39:00 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/23 10:47:52 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_checkcolision(t_gimg *p, t_gimg *o, int precision)
{
	if (p->x > o->x + SS / precision)
		return (0);
	else if (p->x + SS / precision < o->x)
		return (0);
	else if (p->y > o->y + SS / precision)
		return (0);
	else if (p->y + SS / precision < o->y)
		return (0);
	return (1);
}

t_list	*ft_checkcolisionlst(t_gimg *p, t_list *o, int precision)
{
	while (o)
	{
		if (ft_checkcolision(p, o->content, precision))
			return (o);
		o = o->next;
	}
	return (0);
}
