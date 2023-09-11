/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_libft_mods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 22:44:59 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/08 21:30:33 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_strdup_dmh(t_data *data, const char *s1)
{
	char	*str;

	str = dmh(data, ft_strlen(s1) + 1);
	if (str == NULL)
		malloc_error(data);
	ft_memcpy(str, s1, ft_strlen(s1));
	str[ft_strlen(s1)] = '\0';
	return (str);
}

char	*ft_strndup_dmh(t_data *data, const char *s1, size_t n)
{
	char	*str;

	str = dmh(data, n + 1);
	if (str == NULL)
		malloc_error(data);
	ft_memcpy(str, s1, n);
	str[n] = '\0';
	return (str);
}

char	*ft_strjoin_dmh(t_data *data, char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new = dmh(data, ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		malloc_error(data);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
