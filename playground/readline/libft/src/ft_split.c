/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trsctr <trsctr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:19:55 by oandelin          #+#    #+#             */
/*   Updated: 2023/03/24 17:04:09 by trsctr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_countwords
// counts how many substrings needs to be created
// does not simply count the amount of delimiter character
// hence the if statement in the while loop
// returns the amount of words, which is used to allocate
// correct amount of memory for the array
static	size_t	ft_countwords(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] == c)
			i++;
	while (s[i])
	{	
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

// ft_getwordlen
// is used to get the length of each word
// which is used to allocate right amount of memory for each
// substring. stops counting when the string ends
// or character c appears
static	size_t	ft_getwordlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

// ft_freearr
// in case of malloc fail in ft_stringtoarr, this function is used
// to free all allocated memory
static void	ft_freearr(char **strarr)
{
	size_t	i;

	i = 0;
	while (strarr[i])
	{
		free(strarr[i]);
		i++;
	}
	free(strarr);
}

// ft_stringarr
// helper function to split the string to string array and returns the array
// in case of malloc fail frees all allocated memory and returns null
static char	**ft_stringtoarr(char **strarr, const char *s, char c)
{
	size_t	strnr;
	size_t	i;
	size_t	wordlen;

	strnr = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			wordlen = ft_getwordlen(s + i, c);
			strarr[strnr] = ft_substr(s, i, wordlen);
			if (!strarr[strnr])
			{
				ft_freearr(strarr);
				return (NULL);
			}
			i += wordlen;
			strnr++;
		}
		else
			i++;
	}
	strarr[strnr] = NULL;
	return (strarr);
}

// ft_split
// takes a character string s and delimiter character c
// splits string to smaller substrings, splitpoint is c
// allocates memory string array **strarr and its substrings
// returns the string array which ends with a NULL pointer
char	**ft_split(char const *s, char c)
{
	char	**strarr;

	if (!s)
		return (NULL);
	strarr = (char **) malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!strarr)
		return (NULL);
	strarr = ft_stringtoarr(strarr, s, c);
	if (!strarr)
		return (NULL);
	return (strarr);
}
