/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:23:43 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/23 20:36:49 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != 0)
		count++;
	return (count);
}

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	count;
	size_t			strlen;
	char			*str;

	if (!s)
		return (0);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	strlen = ft_strlen((char *)s);
	count = 0;
	while (start < strlen && s[start + count] && count < len)
	{
		str[count] = s[start + count];
		count++;
	}
	str[count] = '\0';
	return (str);
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

void	*ft_calloc(size_t count, size_t size)
{
	void			*mem;
	unsigned char	*str;
	size_t			count1;

	count1 = 0;
	mem = (void *) malloc(count * size);
	if (!mem)
		return (0);
	str = (unsigned char *) mem;
	count1 = 0;
	while (count1 < count * size)
	{
		str[count1] = 0;
		count1++;
	}
	return (mem);
}
