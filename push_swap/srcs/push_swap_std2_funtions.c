/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_std2_funtions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:04:17 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/23 21:14:53 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	int		size;

	if (!len || start >= ft_strlen(s))
		size = 0;
	else if (ft_strlen(s) > (start + len))
		size = len;
	else
		size = ft_strlen(s) - start;
	substr = (char *) malloc (sizeof(char) * (size + 1));
	if (!substr)
		return (0);
	if (size)
		ft_strlcpy(substr, &s[start], size + 1);
	else
		substr[0] = 0;
	return (substr);
}

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != 0)
		count++;
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	if (dstsize < 1 || !dst || !src)
		return (ft_strlen(src));
	count = 0;
	while (count < dstsize - 1 && src[count])
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = 0;
	return (ft_strlen(src));
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
