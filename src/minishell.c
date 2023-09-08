/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:59:13 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/08 11:01:48 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->read_fd = 0;
	exec->write_fd = 1;
	exec->has_heredoc = 0;
	exec->next = NULL;
	exec->token = NULL;
	return (exec);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->env_var = NULL;
	data->exec = NULL;
	data->exit_status = 0;
	return (data);
}

int	main(void)
{
	t_data		*data;
	extern char	**environ;

	data = init_data();
	save_env_var(environ, data);
	prompt(data);
	exit (0);
}
