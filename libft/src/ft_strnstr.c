/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:03:42 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/12 15:12:59 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strnstr
// looks for char string *needle from char string *haystack within
// len amount of bytes in the *haystack
// if *needle is COMPLETELY found within len, then returns pointer
// to the position where *needle start in *haystack
// otherwise returns null
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ndllen;

	if (len == 0 && *needle)
		return (0);
	ndllen = ft_strlen(needle);
	if (ndllen == 0)
		return ((char *)haystack);
	while (*haystack && len >= ndllen)
	{
		if (*needle == *haystack)
		{	
			if (ft_strncmp(haystack, needle, ndllen) == 0)
				return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}
