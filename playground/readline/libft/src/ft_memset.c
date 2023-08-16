/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:22:30 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:05:42 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_memset
// writes len bytes of value c to the string b
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;
	size_t			i;

	i = 0;
	s = (unsigned char *) b;
	while (i < len)
	{
		s[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
