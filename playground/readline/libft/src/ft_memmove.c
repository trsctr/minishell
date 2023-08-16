/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:06 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:05:39 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_memmove
// copies n amount of bytes from sring src to string dst
// the two strings may overlap, copying is done non-destructively
// overlapping is checked by comparing dst & src pointer addresses
// returns dst
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dp;
	unsigned char	*sp;

	sp = (unsigned char *) src;
	dp = (unsigned char *) dst;
	if (dp > sp)
	{
		while (len--)
		{
			dp[len] = sp[len];
		}
	}
	else
		ft_memcpy(dp, sp, len);
	return ((void *)dst);
}
