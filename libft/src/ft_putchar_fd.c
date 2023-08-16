/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:21:18 by oandelin          #+#    #+#             */
/*   Updated: 2023/01/26 13:23:47 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_putchar_fd
// writes single char c to file descriptor fd
int	ft_putchar_fd(char c, int fd)
{
	int	i;

	i = write(fd, &c, 1);
	return (i);
}
