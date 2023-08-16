/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:20:29 by oandelin          #+#    #+#             */
/*   Updated: 2023/01/17 10:15:03 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_putendl_fd
// write string *s to file descriptor fd followed by a newline
int	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = ft_putstr_fd(s, fd);
	i += ft_putchar_fd('\n', fd);
	return (i);
}
