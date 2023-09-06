/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 21:37:53 by akoskine          #+#    #+#             */
/*   Updated: 2022/12/19 21:40:41 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ret;

	if (!s)
		return (0);
	ret = (char *)s;
	while (*ret != (char )c)
	{
		if (*ret == '\0')
			return (0);
		ret++;
	}
	return (ret);
}
