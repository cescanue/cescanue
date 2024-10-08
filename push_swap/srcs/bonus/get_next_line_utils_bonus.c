/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:23:43 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/02 16:44:11 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

char	*ft_strchr(const char *s, int c)
{
	int	count;

	count = 0;
	while (s[count] != 0)
	{
		if (s[count] == (char) c)
			return ((char *) &s[count]);
		count++;
	}
	if (s[count] == (char) c)
		return ((char *) &s[count]);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int			count;
	int			count1;
	char		*str;

	if (!s1 || !s2)
		return (0);
	str = malloc(sizeof(char)
			* (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	if (!str)
		return (0);
	count = 0;
	count1 = 0;
	while (s1[count])
		str[count1++] = s1[count++];
	count = 0;
	while (s2[count])
		str[count1++] = s2[count++];
	str[count1] = '\0';
	return (str);
}
