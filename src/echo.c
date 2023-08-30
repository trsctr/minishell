/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:39:30 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/30 13:57:29 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "utils.h"

void	builtin_echo(t_exec *exec)
{
	int	i;

	i = 1;
	if (exec->argv[1] && !ft_strcmp(exec->argv[1], "-n"))
		i++;
	while (exec->argv[i])
	{
		ft_putstr_fd(exec->argv[i], 1);
		if (exec->argv[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (exec->argv[1] && !ft_strcmp(exec->argv[1], "-n"))
		return ;
	else
		write(1, "\n", 1);
}
