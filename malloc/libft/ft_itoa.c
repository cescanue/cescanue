/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:26:34 by cescanue          #+#    #+#             */
/*   Updated: 2024/10/25 13:14:32 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, char *number, int *index)
{
	if (number)
		number[*index] = c;
	*index += 1;
}

void	ft_myitoa(long int nb, char *number, int *index)
{
	if (nb < 0)
	{
		ft_putchar('-', number, index);
		nb = -nb;
	}
	if (nb <= 9)
		ft_putchar(nb + 48, number, index);
	else if (nb > 9)
	{
		ft_myitoa(nb / 10, number, index);
		ft_myitoa(nb % 10, number, index);
	}
}

char	*ft_itoa(int n)
{
	char	*number;
	int		index;

	number = 0;
	index = 0;
	ft_myitoa(n, number, &index);
	number = (char *) ft_calloc (sizeof(char), index + 1);
	if (!number)
		return (0);
	index = 0;
	ft_myitoa(n, number, &index);
	return (number);
}
