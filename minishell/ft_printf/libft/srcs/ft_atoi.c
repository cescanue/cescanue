/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:31:59 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/07 21:41:59 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	int	count;
	int	nbr;
	int	neg;

	nbr = 0;
	count = 0;
	neg = 0;
	if (str[count] == '+' || str[count] == '-')
	{
		if (str[count] == '-')
			neg = 1;
		count++;
	}
	while (str[count] >= '0' && str[count] <= '9')
	{
		nbr *= 10;
		nbr += str[count] - 48;
		count++;
	}
	if (neg)
		nbr = -nbr;
	if (str[count] == 0 || str[count] == ' ')
		return (nbr);
	return (0);
}
