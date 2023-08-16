/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:19:53 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:23:19 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strchr
// looks for c from *str
// returns pointer to first occurence of c
// or NULL if none are found
char	*ft_strchr(const char *str, int c)
{
	char	chr;

	chr = c;
	while (*str != '\0' && *str != chr)
		str++;
	if (*str == chr)
		return ((char *)str);
	else
		return (NULL);
}
