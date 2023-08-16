/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:19:53 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:03:30 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strrchr
// scans *str for character c
// returns pointer to last appearance of c
// or NULL if none found
char	*ft_strrchr(const char *str, int c)
{
	int		count;
	char	chr;

	chr = c;
	count = 0;
	while (*str != '\0')
	{
		if (*str == chr)
			count++;
		str++;
	}
	if (*str == chr)
		count++;
	if (!count)
		return (NULL);
	else
		while (*str != chr)
			str--;
	return ((char *)str);
}
