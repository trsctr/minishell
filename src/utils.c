/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:46:07 by slampine          #+#    #+#             */
/*   Updated: 2023/09/13 15:32:20 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "env_var.h"

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

int	ft_envsize(t_ev *lst)
{
	int		i;
	t_ev	*curr;

	i = 0;
	curr = lst;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

/**
 * @brief function to clear and free exec list
 * 
 * @param exec 
 */
void	free_exec(t_exec *exec)
{
	t_exec	*temp_exec;
	int 	i;

	while (exec)
	{
		free(exec->cmd);
		i = 0;
		while (exec->argv[i])
		{
			free(exec->argv[i]);
			i++;
		}
		temp_exec = exec->next;
		if (exec->has_heredoc)
		{
			if (exec->read_fd > 2)
				close (exec->read_fd);
			unlink(exec->heredoc);
			free(exec->heredoc);
		}
		free(exec);
		exec = temp_exec;
	}
}

/**
 * @brief prints an error message based on given error code
 * 
 * @param errorcode 
 * @param cmd required if printing an error containing the command
 * or argument
 */
void	ft_errormsg(int errorcode, char *cmd)
{
	if (errorcode == BAD_CMD)
		ft_dprintf(2, "minishell: Command not found: %s\n", cmd);
	else if (errorcode == MALLOC_FAIL)
		ft_dprintf(2, "minishell: Memory allocation failed)\n");
	else if (errorcode == PIPE_FAIL)
		ft_dprintf(2, "minishell: Piping failed\n");
	else if (errorcode == FORK_FAIL)
		ft_dprintf(2, "minishell: Fork error\n");
	else if (errorcode == SYNTAX_ERROR)
		ft_dprintf(2, "minishell: Syntax error\n");
	else if (errorcode == EXPORT_NOT_VALID)
		ft_dprintf(2, "minishell: export: '%s' not a valid identifier\n", cmd);
	else if (errorcode == EXIT_BAD_VALUE)
		ft_dprintf(2, "minishell: exit: %s: numeric argument needed\n", cmd);
	else if (errorcode == FILE_NOT_FOUND)
		ft_dprintf(2, "minishell: %s no such file or directory\n", cmd);
}

void	set_exit_status(t_data *data, int status)
{
	data->exit_status = status;
}

char	*ft_getenv(t_data *data, char *key)
{
	t_ev	*temp;

	temp = ft_find_var(&data->env_var, key);
	if (!temp)
		return (NULL);
	else
		return (temp->value);
}

