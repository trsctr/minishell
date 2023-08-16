/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:59:13 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/16 15:36:41 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	*input;

	while (420)
	{
		input = get_input();
		if (!ft_strncmp(input, "exit", 4))
		{
			ft_putendl_fd("exit", 2);
			clear_history();
			break ;
		}
		if (input[0] != '\0' && input[0] != '\n')
			ft_printf("%s: command not found\n", input);
	}
}

char *get_input(void)
{
	char	*line;

	line = readline("minishell :");
	if (line[0] != '\0' && line[0] != '\n')
		add_history(line);
	return (line);
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	printf("Welcome to minishell\nPlease enter your command below\n\n");
	prompt();
	return (0);
}
