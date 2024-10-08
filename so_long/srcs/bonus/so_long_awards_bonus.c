/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_awards_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:49:12 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/29 09:30:12 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_print_awardsn(t_data *d)
{
	char	*tmpn;
	int		count;
	int		posx;

	posx = SS;
	mlx_put_image_to_window(d->mlx, d->mlx_win,
		ft_getimglst(1, *d->awards)->img, posx, 2);
	count = -1;
	while (count++ < 5)
	{
		posx = SS * 2 + (NUMBERSW * count) + count;
		mlx_put_image_to_window(d->mlx, d->mlx_win,
			ft_getimglst(10, *d->numbers)->img, posx, 10);
	}
	count = 0;
	tmpn = ft_itoa(d->tawards);
	while (tmpn[count])
	{
		posx = SS * 2 + (NUMBERSW * count) + count;
		mlx_put_image_to_window(d->mlx, d->mlx_win,
			ft_getimglst(tmpn[count] - 48, *d->numbers)->img, posx, 10);
		count++;
	}
	free (tmpn);
}

void	ft_checkawards(t_data *d)
{
	t_list	*t;

	t = ft_checkcolisionlst(((t_list *)*d->gp)->content, *d->gawards, 10);
	if (t)
	{
		ft_lstdelonem(d->gawards, t, ft_dellstg);
		d->tawards++;
	}
}

void	ft_checkexit(t_data *d)
{
	t_list	*t;

	t = ft_checkcolisionlst(((t_list *)*d->gp)->content, *d->gexit, 10);
	if (t && !ft_lstsize(*d->gawards))
	{
		ft_printf("You win, you have collected all the");
		ft_printf(" treasures and you have reached the exit.\n");
		ft_clearmem(d);
	}
}
