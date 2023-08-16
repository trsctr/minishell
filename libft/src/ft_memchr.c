/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:19:53 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:05:32 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_memchr
// looks for first occurence c of memory block *s 
// returns pointer to the byte c is located at
// or NULL if no such byte is found within n bytes
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	chr;
	unsigned char	*str;

	chr = c;
	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == chr)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
