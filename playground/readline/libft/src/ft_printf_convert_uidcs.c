/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert_uidcs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:53:30 by oandelin          #+#    #+#             */
/*   Updated: 2023/02/21 16:17:09 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	convert_id(int n)
{
	return (ft_putnbr_fd(n, 1));
}

int	convert_u(unsigned int n)
{
	return (ft_putuint_fd(n, 1));
}

int	convert_c(int c)
{
	return (ft_putchar_fd((char) c, 1));
}

int	convert_str(char *s)
{
	if (!s)
		return (ft_putstr_fd("(null)", 1));
	else
		return (ft_putstr_fd(s, 1));
}
