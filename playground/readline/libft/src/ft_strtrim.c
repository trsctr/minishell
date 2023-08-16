/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:00:47 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/12 15:09:55 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_checkchar is used check if char c is any of the characters specified in
// *set. returns 0 if not, returns 1 if yes
static	int	ft_checkchar(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{	
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

// getstart is used to trim the beginning of the string
// runs checkchar one by one and moves forward if there is a match
// returns pointer to the first point of *str where there is no match
static	const char	*ft_getstart(const char *str, const char *set)
{
	while (ft_checkchar(*str, set))
	{
			str++;
	}
	return (str);
}

// getlenght is used to trim the end of the string
// ft_strlen is used to get the length of the remaining string
// then we move back from the end of the string checking chars one by one
// returns lenght of the trimmed string which is used to allocate right
// amount of memory
static	size_t	ft_getlength(const char *str, const char *set)
{
	size_t	len;

	if (!str[0])
		return (0);
	len = ft_strlen(str);
	while (ft_checkchar(str[len - 1], set))
	{
			len--;
	}
	return (len);
}

// getstring
// once the memory has been allocated ft_getstring is used to
// create the trimmed string *s2 from *s1 which will be len
// amount of characters long
// *s1 is actually the pointer to the beginning of the new string
// which is fetched originally in ft_getstart
// null terminates the string s2 and then returns it to the main function
static	char	*ft_getstring(char *s2, const char *s1, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
			s2[i] = *s1;
			i++;
			s1++;
	}
	s2[i] = '\0';
	return (s2);
}

// ft_strtrim
// allocates memory for char string *s2 which is a trimmed version of
// char string *s1 based in characters specified in char string *set
// characters specified in *set are removed from the beginning and end
// of *s1. for example trimming whitespaces and whatnot
// returns *s2
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	len;

	if (!s1)
		return (NULL);
	len = 0;
	s1 = ft_getstart(s1, set);
	len = ft_getlength(s1, set);
	s2 = (char *) malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	s2 = ft_getstring(s2, s1, len);
	return (s2);
}
