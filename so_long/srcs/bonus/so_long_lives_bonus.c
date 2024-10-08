/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_lives.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:30:44 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/23 20:29:09 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_print_livesn(t_data *d)
{
	char	*tmpn;
	int		count;
	int		posx;

	count = -1;
	while (count++ < 5)
	{
		posx = ((d->mapx - 2) * SS) + (NUMBERSW * count) + count;
		mlx_put_image_to_window(d->mlx, d->mlx_win,
			ft_getimglst(10, *d->numbers)->img, posx, 10);
	}
	count = 0;
	tmpn = ft_itoa(d->lives);
	while (tmpn[count])
	{
		posx = ((d->mapx - 2) * SS) + (NUMBERSW * count) + count;
		mlx_put_image_to_window(d->mlx, d->mlx_win,
			ft_getimglst(tmpn[count] - 48, *d->numbers)->img, posx, 10);
		count++;
	}
	free (tmpn);
}

void	ft_print_lives(t_data *d)
{
	t_img	*img;
	t_img	*img1;

	if (d->lives > d->tlives / 2)
		img = ((t_list *)*d->heart)->next->content;
	else if (d->lives <= (d->tlives / 2) && d->lives > 0)
		img = ((t_list *)*d->heart)->next->next->content;
	else
		img = ((t_list *)*d->heart)->next->next->next->content;
	img1 = ((t_list *)*d->heart)->content;
	mlx_put_image_to_window(d->mlx, d->mlx_win,
		img1->img, (d->mapx - 3) * SS, 2);
	mlx_put_image_to_window(d->mlx, d->mlx_win,
		img->img, (d->mapx - 3) * SS, 2);
	ft_print_livesn(d);
}
