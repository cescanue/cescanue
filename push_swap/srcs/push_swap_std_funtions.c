/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_std_funtions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:37:01 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/23 21:27:25 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_atoi(const char *str)
{
	int	count;
	int	nbr;
	int	neg;

	nbr = 0;
	count = 0;
	neg = 0;
	while (str[count] == ' ' || str[count] == '\t' || str[count] == '\v'
		|| str[count] == '\n' || str[count] == '\r' || str[count] == '\f')
		count++;
	while (str[count] == '+' || str[count] == '-')
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
	return (nbr);
}

int	ft_isnbr(const char *str)
{
	long	nbr;
	int		neg;
	int		valid;

	nbr = 0;
	neg = 0;
	valid = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v'
		|| *str == '\n' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
		neg = 1;
	while (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + *str - 48;
		str++;
		valid = 1;
	}
	if (neg)
		nbr = -nbr;
	if (nbr < -2147483648 || nbr > 2147483647)
		return (0);
	return (valid);
}

int	countwords(const char *s, char c)
{
	int	count;
	int	count1;
	int	words;

	count = 0;
	words = 0;
	while (s[count])
	{
		while (s[count] && s[count] == c)
			count++;
		count1 = count;
		while (s[count1] && s[count1] != c)
			count1++;
		if (count1 - count)
			words++;
		count = count1;
	}
	return (words);
}

char	**ft_freea(char **astr)
{
	int	index;

	index = 0;
	while (astr[index])
	{
		free(astr[index]);
		index++;
	}
	free(astr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		sdat[3];
	char	**astr;

	astr = (char **)malloc(sizeof(char *) * ((sdat[2] = countwords(s, c)) + 1));
	if (!s || !astr)
		return (0);
	ft_memset (sdat, 0, sizeof(int) * 3);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			sdat[1] = 0;
			while (*(s + sdat[1]) && *(s + sdat[1]) != c)
				sdat[1]++;
			astr[sdat[0]] = ft_substr(s, 0, sdat[1]);
			if (!astr[sdat[0]])
				return (ft_freea(astr));
			sdat[0]++;
			s += sdat[1];
		}
	}
	astr[sdat[0]] = 0;
	return (astr);
}
