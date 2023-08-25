/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:59:13 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/25 14:29:08 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
// void	prompt(t_data *data)
// {
// 	char	*input;

// 	(void) ms;
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

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->env_var = NULL;
	data->exec = NULL;//malloc(sizeof(t_ev));
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
