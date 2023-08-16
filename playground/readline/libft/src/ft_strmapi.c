/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:46:23 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/12 15:18:11 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strmapi
// allocates memory for a new string based on the size of char string *s
// then scans through string *s performing function f and filling
// *newstr with the results of function f (like modified characters)
// returns the new modified string
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*newstr;
	unsigned int	i;
	size_t			len;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	newstr = (char *) malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
