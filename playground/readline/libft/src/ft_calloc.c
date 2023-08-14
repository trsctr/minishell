/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:13:37 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:04:59 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_calloc
// allocates memory space for 'count' objects that are each 'size' of bytes
// then fills the allocated memory with bytes of value zero
// returns pointer to the memory block
void	*ft_calloc(size_t count, size_t size)
{
	void	*blk;
	size_t	total;

	if (!count || !size)
		return (ft_calloc(1, 1));
	total = size * count;
	if (total / count != size)
		return (NULL);
	blk = malloc(total);
	if (!blk)
		return (NULL);
	ft_bzero(blk, total);
	return (blk);
}
