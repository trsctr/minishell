/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:22:30 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:04:56 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	ft_bzero
//	fills memory block *b with zeroes and returns it
void	*ft_bzero(void *b, size_t len)
{
	unsigned char	*s;
	size_t			i;

	i = 0;
	s = (unsigned char *) b;
	while (i < len)
	{
		s[i] = 0;
		i++;
	}
	return (b);
}
