/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:04:46 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/04 17:36:04 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"

static int	print_str(char *s)
{
	if (!s)
		return (ft_putstr_fd("(null)", 2));
	else
		return (ft_putstr_fd(s, 2));
}

/**
 * @brief basic version of ft_printf that outputs error messages
 * to standard error
 * @param format 
 * @param ... 
 * @return int characters printed
 */
int	ft_printf_stderr(const char *format, ...)
{
	va_list	args;
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == 's')
		{
			i++;
			ret = print_str(va_arg(args, char *));
		}
		else if (format[i] == '%' && format[i + 1] == '%')
		{
			i++;
			ret += ft_putchar_fd(format[i], 2);
		}
		else if (format[i] != '%')
			ret += ft_putchar_fd(format[i], 2);
		i++;
	}
	va_end(args);
	return (ret);
}
