/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:49:06 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/18 18:14:38 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

/**
 * @brief function that clears the main data struct before exiting
 * 
 * @param data 
 */
void	clear_data(t_data *data)
{
	clear_history();
	ft_clear_evlist(data);
	if (data->pipe_count)
		free(data->pipes);
	if (data)
		free(data);
}

/**
 * @brief deletes and frees the linked list so we can exit gracefully
 * 
 * @param ms 
 */
void	ft_clear_evlist(t_data *data)
{
	t_ev	*temp;
	t_ev	*var;

	var = data->env_var;
	while (var)
	{
		free(var->key);
		free(var->value);
		temp = var->next;
		free(var);
		var = temp;
	}
}

/**
 * @brief helper function for clearing a char array
 * 
 * @param array 
 */
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/**
 * @brief function to clear and free exec list
 * 
 * @param exec 
 */
void	free_exec(t_exec *exec)
{
	t_exec	*temp;

	while (exec)
	{
		free(exec->cmd);
		if (exec->argv)
			free_array(exec->argv);
		if (exec->has_heredoc)
		{
			if (exec->read_fd > 2)
				close(exec->read_fd);
			unlink(exec->heredoc);
			free(exec->heredoc);
		}
		temp = exec->next;
		free(exec);
		exec = temp;
	}
}
