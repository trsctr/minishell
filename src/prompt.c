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
