/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert_hex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:43:44 by oandelin          #+#    #+#             */
/*   Updated: 2023/04/04 21:15:06 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printhex(unsigned long n, char c)
{
	int	i;

	i = 0;
	if (n > 15)
	{
		i += printhex(n / 16, c);
		i += printhex(n % 16, c);
	}
	else if (n > 9)
		i += ft_putchar_fd(n + c, 1);
	else if (n < 10)
		i += ft_putchar_fd(n + '0', 1);
	return (i);
}

int	convert_x(unsigned int n, char c)
{
	int	ret;

	if (c == 'X')
		c = 55;
	else
		c = 87;
	ret = printhex((unsigned long)n, c);
	return (ret);
}

int	convert_p(void *p)
{
	int	ret;

	ret = ft_putstr_fd("0x", 1);
	ret += printhex((unsigned long)p, 87);
	return (ret);
}
