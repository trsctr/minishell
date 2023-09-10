/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:46:07 by slampine          #+#    #+#             */
/*   Updated: 2023/09/10 19:57:02 by oandelin         ###   ########.fr       */
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
	int		i;
	t_exec	*temp;

	while (exec)
	{
		temp = exec->next;
		i = 0;
		while (exec->argv[i])
		{
			free(exec->argv[i]);
			i++;
		}
		free(exec->argv);
		exec->next = NULL;
		exec = temp;
	}
}

/**
 * @brief prints an error message based on given error code
 * 
 * @param errorcode 
 * @param cmd required if printing "bad command or file name"
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
		return (ft_strdup(""));
	else
		return (ft_strdup(temp->value));
}
