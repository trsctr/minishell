/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:59:13 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/12 12:42:05 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "utils.h"
#include "env_var.h"

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
	if (!data)
		return (NULL);
	data->env_var = NULL;
	data->exec = NULL;
	data->exit_status = 0;
	return (data);
}

int	main(int argc, char **argv, char **environ)
{
	t_data		*data;

	(void) argv;
	if (argc > 1)
	{
		ft_dprintf(2, "Please run me without arguments\n");
		exit(1);
	}
	if (argc == 1)
	{
		data = init_data();
		if (!data)
		{
			ft_errormsg(MALLOC_FAIL, NULL);
			exit (1);
		}
		terminal_setup(data);
		save_env_var(environ, data);
		prompt(data);
		terminal_reset(data);
		clear_data(data);
		exit(0);
	}
}
