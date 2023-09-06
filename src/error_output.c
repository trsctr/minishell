/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:04:46 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/06 18:25:55 by oandelin         ###   ########.fr       */
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

/**
 * @brief prints an error message based on given error code
 * 
 * @param errorcode 
 * @param cmd required if printing "bad command or file name"
 */
void	ft_errormsg(int errorcode, char *cmd)
{
	if (errorcode == BAD_CMD)
		ft_printf_stderr("minishell: Command not found: %s\n", cmd);
	else if (errorcode == MALLOC_FAIL)
		ft_printf_stderr("minishell: Memory allocation failed)\n");
	else if (errorcode == PIPE_FAIL)
		ft_printf_stderr("minishell: Piping failed\n");
	else if (errorcode == SYNTAX_ERROR)
		ft_printf_stderr("minishell: Syntax error\n");
}
