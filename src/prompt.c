/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:24:25 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/08 15:32:02 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "builtins.h"
#include "executor.h"
#include "env_var.h"
#include "utils.h"
#include "heredoc.h"

/**
 * @brief creates pipes if necessary and runs every command
 * 	(still in progress)
 * @param data 
 */
void	run_command_line(t_data *data)
{
	t_exec	*cmd;
	int		pipe_fd[OPEN_MAX][2];
	int		i;
	int		input;
	int		status;

	i = 0;
	input = 0;
	cmd = data->exec;
	handle_heredocs(data);
	while (cmd)
	{
		if (cmd->next)
		{
			status = pipe(pipe_fd[i]);
			if (status == -1)
			{
				printf("Error with pipe\n");
				break ;
			}
			cmd->read_fd = input;
			cmd->write_fd = pipe_fd[i][1];
			if (executor(data, cmd))
				break ;
			input = pipe_fd[i][0];
		}
		else
		{
			cmd->read_fd = input;
			if (executor(data, cmd))
				perror("");
		}
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

	while (420)
	{
		input = get_input();
		if (!input || !ft_strncmp(input, "exit", 4))
		{
			ft_putendl_fd("exit", 2);
			if (input)
				free(input);
			clear_history();
			break ;
		}
		else if (input[0] == '\0' || input[0] == '\n' || !only_spaces(input))
		{
			free(input);
			continue ;
		}
		else if (is_builtin(input))
		{
			data->exec->argv = ft_split(input, ' ');
			data->exec->cmd = data->exec->argv[0];
			run_builtin(data->exec, is_builtin(input), data);
		}
		else if (input[0] != '\0' && input[0] != '\n')
		{
			data->exec->argv = ft_split(input, ' ');
			data->exec->cmd = data->exec->argv[0];
			run_command_line(data);
		}
		free_exec(data->exec);
		free(input);
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
	char				*line;

	line = readline(BYELLOW PROMPT RESET);
	if (!line)
		return (NULL);
	if (line[0] != '\0' && line[0] != '\n' && only_spaces(line))
		add_history(line);
	return (line);
}

