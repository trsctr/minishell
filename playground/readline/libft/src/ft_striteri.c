/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:34:06 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:02:50 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_striteri
// iterates through char string *s
// and performs function f for each of the characters in the string
// basically same as strmapi but modifies the string directly instead 
// of creating a new string
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (*s)
	{
		f(i, s);
		i++;
		s++;
	}
}
