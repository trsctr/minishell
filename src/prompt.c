/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:24:25 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/19 17:00:55 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "builtins.h"


/**
 * @brief this function runs the command prompt. it receives user input from
 * the function get_input which actually shows the command prompt, and will
 * send it to lexer/parser. if we receive NULL from the get_input function,
 * it means user has pressed CTRL+D and in that case we exit.
 * 
 * @param ms 
 */
void	prompt(t_ms *ms)
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
			//ft_lstclear(&ms->env_var, &free);
			//free(ms);
			clear_history();
			break ;
		}
		else if (!ft_strncmp(input, "cd ", 3))
			builtin_cd(input+3, ms);
		else if (!ft_strncmp(input, "env", 3))
			builtin_env(ms);
		else if (!ft_strncmp(input, "pwd", 3))
			builtin_pwd();
		else if (input[0] != '\0' && input[0] != '\n')
			ft_printf("%s: %s\n", input, CMD_NOT_FOUND);
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
