/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:03:36 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/18 19:39:55 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_convert_status(char *str)
{
	int	status;

	if (!ft_isanumber(str))
	{
		ft_errormsg(EXIT_BAD_VALUE, str);
		status = 255;
	}
	else
	{
		status = ft_atoi(str);
		if (status > 255)
			status = status % 256;
		while (status < 0)
			status += 256;
	}
	return (status);
}

/**
 * @brief exit exits the shell. or first prints the exit message
 * and exits with the numerical argument user has given, or give an error
 * message if user gives something else
 * 
 * @param data 
 * @param exec 
 */
void	builtin_exit(t_data *data, t_exec *exec)
{
	int	status;

	if (data->pipe_count == 0)
		status = data->exit_status;
	else
		status = 0;
	if (exec && exec->argv[1])
		status = exit_convert_status(exec->argv[1]);
	if (data->pipe_count == 0)
	{
		ft_printf("exit\n");
		reset_signals();
		terminal_reset(data);
		clear_data(data);
		exit(status);
	}
	set_exit_status(data, status);
	return ;
}
