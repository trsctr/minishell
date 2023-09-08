/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert_hex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:43:44 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/08 16:56:09 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printhex(unsigned long n, char c, int fd)
{
	int	i;

	i = 0;
	if (n > 15)
	{
		i += printhex(n / 16, c, fd);
		i += printhex(n % 16, c, fd);
	}
	else if (n > 9)
		i += ft_putchar_fd(n + c, fd);
	else if (n < 10)
		i += ft_putchar_fd(n + '0', fd);
	return (i);
}

int	convert_x(unsigned int n, char c, int fd)
{
	int	ret;

	if (c == 'X')
		c = 55;
	else
		c = 87;
	ret = printhex((unsigned long)n, c, fd);
	return (ret);
}

int	convert_p(void *p, int fd)
{
	int	ret;

	ret = ft_putstr_fd("0x", fd);
	ret += printhex((unsigned long)p, 87, fd);
	return (ret);
}
