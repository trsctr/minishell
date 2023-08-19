/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:59:13 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/18 15:37:48 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
// void	prompt(t_ms *ms)
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

t_ms	*init_ms(void)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	return (ms);
}

int	main(int ac, char **av, char **env)
{
	t_ms *ms = NULL;

	(void) ac;
	(void) av;
	(void) env;
	ms = init_ms();
	prompt(ms);
	return (0);
}
