/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:46:07 by slampine          #+#    #+#             */
/*   Updated: 2023/09/16 19:05:45 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_dprintf(2, "minishell: Memory allocation failed\n");
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
	else if (errorcode == CMD_IS_DIR)
		ft_dprintf(2, "minishell: %s is a directory\n", cmd);
	else if (errorcode == EXEC_FAIL)
		ft_dprintf(2, "minishell: %s: execution error\n", cmd);
	else if (errorcode == PERMISSION_DENIED)
		ft_dprintf(2, "minishell: %s: permission denied\n", cmd);
}

void	set_exit_status(t_data *data, int status)
{
	data->exit_status = status;
}

/**
 * @brief our version of getenv function that retrieves the environment
 * variable from the linked list in the main data struct
 * 
 * @param data main data struct
 * @param key keyword of the variable
 * @return char* value of the variable, or NULL if not found
 */
char	*ft_getenv(t_data *data, char *key)
{
	t_ev	*temp;

	temp = ft_find_var(&data->env_var, key);
	if (!temp)
		return (NULL);
	else
		return (temp->value);
}

/**
 * @brief this function is a helper function for builtin_export and builtin_unset
 * key can contain alphanumeric characters and underscores
 * but can't start with a digit
 * 
 * @param key 
 * @return int returns 1 if key is valid, 0 if not.
 */
int	key_is_valid(char *key)
{
	int	i;

	i = 0;
	if (key[0] == '\0' || ft_isdigit(key[0]))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}