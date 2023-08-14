/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:32:06 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:05:36 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_memcpy
// copies n amount of bytes memory block src to memory dst
// returns dst
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dp;
	unsigned char	*sp;

	dp = (unsigned char *) dst;
	sp = (unsigned char *) src;
	if (dp || sp)
	{
		while (n--)
		{		
			*dp = *sp;
			dp++;
			sp++;
		}
	}
	return (dst);
}
