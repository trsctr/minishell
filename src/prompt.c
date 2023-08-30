/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:24:25 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/30 14:04:27 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "builtins.h"
#include "executor.h"
#include "env_var.h"

void run_command_line(t_data *data)
{
	t_exec	*cmd;
	int		pipe_fd[7][2];
	int		i;

	i = 0;
	cmd = data->exec;
	while (cmd)
	{
		if (cmd->next)
		{
			pipe(pipe_fd[i]);
			cmd->write_fd = pipe_fd[i][1];
			cmd->next->read_fd = pipe_fd[i][0];
		}
		executor(data, cmd);
		cmd = cmd->next;
		i++;
	}
}

/**
 * @brief this function runs the command prompt. it receives user input from
 * the function get_input which actually shows the command prompt, and will
 * send it to lexer/parser. if we receive NULL from the get_input function,
 * it means user has pressed CTRL+D and in that case we exit.
 * 
 * @param data 
 */
void	prompt(t_data *data)
{
	char	*input;
	// int		saved_out;
	// int		saved_in;
	int		i;

	while (420)
	{
		input = get_input();
		if (!input || !ft_strncmp(input, "exit", 4))
		{
			ft_putendl_fd("exit", 2);
			if (input)
				free(input);
			//ft_lstclear(&data->env_var, &free);
			//free(data);
			//free(data->exec->next);
			clear_history();
			break ;
		}
		// else if (is_builtin(input))
		// {
		// 	data->exec->argv = ft_split(input, ' ');
		// 	data->exec->cmd = data->exec->argv[0];
		// 	run_builtin(data->exec, is_builtin(input), data);
		// 	//run_builtin(input, is_builtin(input), data);
		// }
		else
		{
			// data->exec->argv = ft_split(input, ' ');
			// data->exec->cmd = data->exec->argv[0];
			// data->exec->write_fd = open("outfile", O_CREAT | O_RDWR | O_APPEND, 0777);
			// data->exec->read_fd = open("infile", O_RDONLY);
			// saved_out = dup(1);
			// saved_in = dup(0);
			// dup2(data->exec->write_fd, 1);
			// dup2(data->exec->read_fd, 0);
			// old_executor(input, data);
			// executor(data, data->exec);
			// dup2(saved_out, 1);
			// dup2(saved_in, 0);
			// close(saved_out);
			// close(saved_in);
			run_command_line(data);
		}
			//ft_printf("%s: %s\n", input, CMD_NOT_FOUND);
		free(input);
		//free(data->exec->cmd);
		i = 0;
		while (data->exec->argv[i])
		{
		//	free(data->exec->argv[i]);
			i++;
		}
		//free(data->exec->argv);
	}
}

/**
 * @brief displays the command prompt using readline to get the user input
 * and listens to possible signals from the user, but doesn't display the signals
 * on terminal.
 * if user presses ctrl+d when the line is empty, readline receives EOF
 * and in that case we return a NULL. if the command we receive is not empty
 * we will save it to history with add_history function.
 * in the end signal and terminal settings are reset and line is returned.
 * 
 * @return 
 */

char	*get_input(void)
{
	char	*line;

	toggle_echoctl();
	listen_signals();
	line = readline(BYELLOW PROMPT RESET);
	if (!line)
	{
		toggle_echoctl();
		reset_signals();
		return (NULL);
	}
	if (line[0] != '\0' && line[0] != '\n')
		add_history(line);
	toggle_echoctl();
	reset_signals();
	return (line);
}
