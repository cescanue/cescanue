/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:59:33 by cescanue          #+#    #+#             */
/*   Updated: 2024/10/25 13:14:32 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
