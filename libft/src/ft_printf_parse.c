/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:55:55 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/08 16:57:06 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_specifier(const char *format, va_list args, int i, int fd)
{
	if (format[i] == '\0')
		return (0);
	else if (format[i] == 'i' || format[i] == 'd')
		return (convert_id(va_arg(args, int), fd));
	else if (format[i] == 'c')
		return (convert_c(va_arg(args, int), fd));
	else if (format[i] == 'u')
		return (convert_u(va_arg(args, unsigned int), fd));
	else if (format[i] == 'x' || format[i] == 'X')
		return (convert_x(va_arg(args, unsigned int), format[i], fd));
	else if (format[i] == 's')
		return (convert_str(va_arg(args, char *), fd));
	else if (format[i] == 'p')
		return (convert_p(va_arg(args, void *), fd));
	else if (format[i] == '%')
		return (ft_putchar_fd('%', fd));
	return (ft_putchar_fd(format[i], fd));
}

int	parse_format(const char *format, va_list args, int fd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			ret += check_specifier(format, args, i, fd);
		}
		else if (format[i] != '%')
			ret += ft_putchar_fd(format[i], fd);
		i++;
	}
	return (ret);
}
