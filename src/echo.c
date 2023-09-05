/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:39:30 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/30 15:04:49 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "utils.h"

/**
* @brief mimics the builtin "echo" command in bash
* takes in the command with args as *exec, and prints
* all the arguments separately with ft_putstr_fd in the loop
* and writes an empty space after each string, except if the said string is last
*
* @param exec contains the command, arguments and outfile fd
*/
void	builtin_echo(t_exec *exec)
{
	int	i;

	i = 1;
	if (exec->argv[1] && !ft_strcmp(exec->argv[1], "-n"))
		i++;
	while (exec->argv[i])
	{
		ft_putstr_fd(exec->argv[i], exec->write_fd);
		if (exec->argv[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (exec->argv[1] && !ft_strcmp(exec->argv[1], "-n"))
		return ;
	else
		write(1, "\n", 1);
}
