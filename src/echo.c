/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:39:30 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/25 14:43:27 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	builtin_echo(t_data *data, t_exec *exec)
{
	int	i;

	(void) data;
	i = 1;
	if (!ft_strcmp(exec->argv[1], "-n"))
		i++;
	while (exec->argv[i])
	{
		ft_putstr_fd(exec->argv[i], 1);
		if (exec->argv[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!ft_strcmp(exec->argv[1], "-n"))
		return ;
	else
		write(1, "\n", 1);
}
