/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:59:13 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/01 14:04:47 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
// void	prompt(t_data *data)
// {
// 	char	*input;

// 	(void) data;
// 	while (420)
// 	{
// 		input = get_input();
// 		if (!ft_strncmp(input, "exit", 4))
// 		{
// 			ft_putendl_fd("exit", 2);
// 			clear_history();
// 			break ;
// 		}
// 		if (input[0] != '\0' && input[0] != '\n')
// 			ft_printf("%s: %s\n", input, CMD_NOT_FOUND);
// 	}
// }

// char	*get_input(void)
// {
// 	char	*line;

// 	line = readline(BYELLOW PROMPT RESET);
// 	if (line[0] != '\0' && line[0] != '\n')
// 		add_history(line);
// 	return (line);
// }

t_exec	*init_exec(void)
{
	t_exec	*exec;
	t_exec	*sec;
	t_exec	*thrd;
	t_exec	*frth;

	exec = malloc(sizeof(t_exec));
	sec = malloc(sizeof(t_exec));
	thrd = malloc(sizeof(t_exec));
	frth = malloc(sizeof(t_exec));
	exec->read_fd = 0;
	exec->write_fd = 1;
	exec->argv = ft_split("ls -l", ' ');
	exec->cmd = exec->argv[0];
	exec->next = NULL;
	sec->read_fd = 0;
	sec->write_fd = 1;
	sec->argv = ft_split("grep drw", ' ');
	sec->cmd = sec->argv[0];
	sec->next = thrd;
	thrd->read_fd = 0;
	thrd->write_fd = 1;
	thrd->argv = ft_split("grep obj", ' ');
	thrd->cmd = thrd->argv[0];
	thrd->next = NULL;
	frth->read_fd = 0;
	frth->write_fd = 1;
	frth->argv = ft_split("wc -l", ' ');
	frth->cmd = frth->argv[0];
	frth->next = NULL;
	return (exec);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->env_var = NULL;//malloc(sizeof(t_ev));
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
