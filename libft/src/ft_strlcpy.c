/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:38:40 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:03:02 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strlcpy
// copies *src to *dst for dstsize-1 amount of characters
// null terminates it if dstsize is not 0
// returns the length of the string the function tried to create (length of src)
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	count;

	srclen = 0;
	count = 0;
	while (src[srclen] != '\0')
	{
		if (dstsize > 1)
		{
			dst[count] = src[srclen];
			count++;
			dstsize--;
		}
		srclen++;
	}
	if (dstsize)
		dst[count] = '\0';
	return (srclen);
}
