/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:24:25 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/11 17:20:42 by oandelin         ###   ########.fr       */
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
	t_exec	*exec;

	exec = data->exec;
	while (exec)
	{
		if (exec->cmd != NULL)
		{
			if (is_builtin(exec->cmd))
				run_builtin(exec, is_builtin(exec->cmd), data);
			else
				executor(data, exec);
		}
		exec = exec->next;
	}
	exec = data->exec;
	free_exec(data->exec);
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
		if (!input)
		{
			if (input)
				free(input);
			terminal_reset(data);
			clear_data(data);
			exit(0);
		}
		else if (input[0] == '\0' || input[0] == '\n' || !only_spaces(input))
		{
			free(input);
			continue ;
		}
		data->input = input;
		lexer(data);
		free(input);
		if (check_syntax(data))
			continue ;
		parser(data);
		run_command_line(data);
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
