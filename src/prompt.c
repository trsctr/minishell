/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:24:25 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/14 14:32:12 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "builtins.h"
#include "executor.h"
#include "env_var.h"
#include "utils.h"
#include "heredoc.h"

void	ft_wait_cmds(t_data *data)
{
	t_exec	*exec;
	int		status;

	exec = data->exec;
	while (exec)
	{
		if (exec->pid)
		{
			waitpid(exec->pid, &status, 0);
			if (g_sig_status)
				set_exit_status(data, 130);
			else if (status == 0)
				set_exit_status(data, 0);
			else
				set_exit_status(data, WIFEXITED(status));
		}
		exec = exec->next;
	}
}

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
	ft_wait_cmds(data);
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
		g_sig_status = 0;
		terminal_setup(data);
		input = get_input();
		if (!input)
			builtin_exit(data, NULL);
		else if (input[0] == '\0' || input[0] == '\n' || !only_spaces(input))
		{
			free(input);
			continue ;
		}
		data->input = input;
		lexer(data);
		if (check_syntax(data))
			continue ;
		free(input);
		if (parser(data) == 0)
			run_command_line(data);
		free_exec(data->exec);
		terminal_reset(data);
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
