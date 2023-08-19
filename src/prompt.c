/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:24:25 by oandelin          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/19 14:36:37 by oandelin         ###   ########.fr       */
=======
/*   Updated: 2023/08/19 18:16:50 by oandelin         ###   ########.fr       */
>>>>>>> 91b38a9... reworked saving env vars
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"

void	prompt(t_ms *ms)
{
	char	*input;

	(void) ms;
	while (420)
	{
		input = get_input();
		if (!input || !ft_strncmp(input, "exit", 4))
		{
			ft_putendl_fd("exit", 2);
<<<<<<< HEAD
=======
			if (input)
				free(input);
			//ft_lstclear(&ms->env_var, &free);
			//free(ms);
>>>>>>> 91b38a9... reworked saving env vars
			clear_history();
			break ;
		}
		else if (input[0] != '\0' && input[0] != '\n')
			ft_printf("%s: %s\n", input, CMD_NOT_FOUND);
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
