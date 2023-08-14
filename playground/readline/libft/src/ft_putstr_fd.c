/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:20:29 by oandelin          #+#    #+#             */
/*   Updated: 2023/01/17 10:23:14 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_putstr_fd
// writes character string s to file descriptor fd
int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;
	int		i;

	if (!s)
		return (0);
	len = ft_strlen(s);
	i = write(fd, s, len);
	return (i);
}
