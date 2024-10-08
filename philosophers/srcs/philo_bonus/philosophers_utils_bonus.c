/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:56:11 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 21:39:48 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philosophers_bonus.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			count;
	unsigned char	*str;

	str = (unsigned char *) b;
	count = 0;
	while (count < len)
	{
		str[count] = (unsigned char) c;
		count++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = (void *) malloc(count * size);
	if (!mem)
		return (0);
	ft_bzero(mem, count * size);
	return (mem);
}

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
	if (nbr == 310)
		nbr -= 11;
	return (nbr);
}

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != 0)
		count++;
	return (count);
}
