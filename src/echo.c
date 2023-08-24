/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:39:30 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/23 17:34:32 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	builtin_echo(t_ms *ms, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->argcount > 0 && !ft_strcmp(cmd->arg[0], "-n"))
		i++;
	while (i < cmd->argcount)
	{
		ft_putstr_fd(cmd->arg[i], 1);
		if (i < cmd->argcount - 1)
			write(1, " ", 1);
		i++;
	}
	if (cmd->argcount > 0 && !ft_strcmp(cmd->arg[0], "-n"))
		return ;
	else
		write(1, "\n", 1);
}
