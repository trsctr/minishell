/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:38:40 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:02:58 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strlcat
// concantenates strings *src & *dst for dstsize amount of characters if
// is enough space in *dst to do that, and then null terminates it
// if there isn't enough space in *dst, then it doesn't touch it
// returns either the length of the created string
// or the length of the string that it tried to create
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	total;
	size_t	i;

	i = 0;
	dstlen = 0;
	srclen = ft_strlen((char *)src);
	if (dst)
		dstlen = ft_strlen((char *)dst);
	if (dstsize > dstlen)
	{	
		total = srclen + dstlen;
		while (dstlen < (dstsize -1) && src[i] != '\0')
		{
			dst[dstlen] = src[i];
			i++;
			dstlen++;
		}
		dst[dstlen] = '\0';
		return (total);
	}
	else
		return (srclen + dstsize);
}
