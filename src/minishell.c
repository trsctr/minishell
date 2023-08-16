/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:59:13 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/16 14:07:44 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	*line;

	while (420)
	{
		line = readline("minishell : ");
		if (!ft_strncmp(line, "exit", 4))
		{
			ft_putendl_fd("exit", 2);
			clear_history();
			break ;
		}
		else
			ft_printf("%s: Command not found\n", line);
		add_history(line);
	}
}

int	main(void)
{
	printf("Welcome to minishell\nPlease enter your command below\n\n");
	prompt();
	return (0);
}