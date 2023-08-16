/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:12:14 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/12 14:27:45 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strjoin
// allocates memory for s3 based sizes of strings s1 and s2
// then concatenates s1 and s2 to the newly created s3 and null terminates it
// returns s3
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	size_t	len1;
	size_t	len2;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = (char *) malloc(sizeof(char) * (len1 + len2 + 1));
	if (!s3)
		return (NULL);
	while (*s1)
		s3[i++] = *s1++;
	while (*s2)
		s3[i++] = *s2++;
	s3[i] = '\0';
	return (s3);
}
