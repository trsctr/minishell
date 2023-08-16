/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:15:51 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/12 15:06:04 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strdup
// allocates memory for char string s2
// and then copies the contents of s1 to s2
// null terminates and returns s2
char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	s2 = (char *) malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	while (i < len)
	{
			s2[i] = s1[i];
			i++;
	}
	s2[i] = '\0';
	return (s2);
}
