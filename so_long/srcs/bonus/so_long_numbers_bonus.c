/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_numbers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:10:52 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/23 11:45:10 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_img	*ft_getimglst(int pos, t_list *lst)
{
	int	count;

	count = 0;
	while (lst && count != pos)
	{
		lst = lst->next;
		count++;
	}
	return (lst->content);
}

void	ft_printmo(t_data *d)
{
	char	*tmpn;
	int		count;
	int		posx;

	count = 0;
	tmpn = ft_itoa(d->pmv);
	while (tmpn[count])
	{
		posx = ((((d->mapx * SS) / 2) - (NUMBERSW * 2))
				+ (NUMBERSW * count)) + count;
		mlx_put_image_to_window(d->mlx, d->mlx_win,
			ft_getimglst(10, *d->numbers)->img, posx, 10);
		mlx_put_image_to_window(d->mlx, d->mlx_win,
			ft_getimglst(tmpn[count] - 48, *d->numbers)->img, posx, 10);
		count++;
	}
	free (tmpn);
}
