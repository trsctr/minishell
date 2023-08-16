/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:30:43 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/12 15:10:59 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_substr
// allocates memory for the substring which is created from char string *s
// based on parameters start and len
// start specifies where in *s the new string starts
// and len is the lenght of the new string
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			srclen;
	int				i;

	i = 0;
	if (!s)
		return (NULL);
	srclen = ft_strlen (s);
	if (len > srclen)
		len = srclen;
	if (start > srclen)
		len = 0;
	sub = (char *) malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (len)
	{
			sub[i] = s[start];
			start++;
			i++;
			len--;
	}
	sub[i] = '\0';
	return (sub);
}
