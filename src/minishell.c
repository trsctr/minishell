/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:59:13 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/06 14:32:33 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"

t_exec	*init_exec(void)
{
	t_exec	*exec;
	// t_exec	*sec;
	// t_exec	*thrd;
	// t_exec	*frth;

	exec = malloc(sizeof(t_exec));
	// sec = malloc(sizeof(t_exec));
	// thrd = malloc(sizeof(t_exec));
	// frth = malloc(sizeof(t_exec));
	exec->read_fd = 0;
	exec->write_fd = 1;
	// exec->argv = ft_split("ls -l", ' ');
	// exec->cmd = exec->argv[0];
	exec->redir_out = 0;
	exec->outfile = "outfile";
	exec->redir_in = 2;
	exec->infile = "infile";
	exec->delim = "stop";
	exec->next = NULL;
	// sec->read_fd = 0;
	// sec->write_fd = 1;
	// sec->argv = ft_split("grep obj", ' ');
	// sec->cmd = sec->argv[0];
	// sec->redir_out = 0;
	// sec->outfile = "outfile";
	// sec->redir_in = 0;
	// sec->next = NULL;
	// thrd->read_fd = 0;
	// thrd->write_fd = 1;
	// thrd->argv = ft_split("grep obj", ' ');
	// thrd->cmd = thrd->argv[0];
	// thrd->redir_in = 0;
	// thrd->redir_out = 0;
	// thrd->infile = "oufile";
	// thrd->next = NULL;
	// frth->read_fd = 0;
	// frth->write_fd = 1;
	// frth->argv = ft_split("wc -l", ' ');
	// frth->cmd = frth->argv[0];
	// frth->next = NULL;
	return (exec);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->env_var = NULL;
	data->exec = init_exec();
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
