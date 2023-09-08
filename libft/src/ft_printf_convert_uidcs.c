/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert_uidcs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:53:30 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/08 16:54:58 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	convert_id(int n, int fd)
{
	return (ft_putnbr_fd(n, fd));
}

int	convert_u(unsigned int n, int fd)
{
	return (ft_putuint_fd(n, fd));
}

int	convert_c(int c, int fd)
{
	return (ft_putchar_fd((char) c, fd));
}

int	convert_str(char *s, int fd)
{
	if (!s)
		return (ft_putstr_fd("(null)", fd));
	else
		return (ft_putstr_fd(s, fd));
}
