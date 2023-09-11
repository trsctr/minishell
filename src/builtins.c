/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:54:26 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/11 15:29:43 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "env_var.h"
#include "prompt.h"

/**
 * @brief built in pwd command uses getcwd to get current working directory
 * which is then printed to fd specified in the command *exec
 * if there are any arguments involved, an error message is printed
 * 
 * @param exec contains command, arguments and file descriptor for output
 */
void	builtin_pwd(t_data *data, t_exec *exec)
{
	char	*wd;
	if (!exec->argv[1])
	{
		wd = getcwd(NULL, 0);
		ft_putendl_fd(wd, exec->write_fd);
		set_exit_status(data, 0);
		free(wd);
	}
	else
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		set_exit_status(data, 1);
	}
}

/**
 * @brief builtin env command, prints out the environment variables
 * which can be found from the main data struct
 * 
 * @param data 
 */
void	builtin_env(t_data *data, t_exec *exec)
{
	t_ev	*curr;

	curr = data->env_var;
	while (curr)
	{
		ft_dprintf(exec->write_fd, "%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	set_exit_status(data, 0);
}

/**
 * @brief builtin command unset. removes env vars if they can be found
 * with they given keywords which are received from the string array
 * exec->argv
 * 
 * if said key is not found, nothing is done
 * 
 * @param data 
 * @param exec 
 */
void	builtin_unset(t_data *data, t_exec *exec)
{
	int	i;
	int	error;

	error = 0;
	i = 1;
	while (exec->argv[i])
	{
		if (!key_is_valid(exec->argv[i]))
		{
			ft_dprintf(2, "unset: '%s' not a valid identifier\n", exec->argv[i]);
			error = 1;
		}
		ft_delete_var(&data->env_var, exec->argv[i]);
		i++;
	}
	set_exit_status(data, error);
}

void	builtin_exit(t_data *data, t_exec *exec)
{
	int	status;

	status = 0;
	if (!exec->argv[1])
		ft_printf("exit\n");
	else
	{
		if (!ft_isanumber(exec->argv[1]))
		{
			ft_errormsg(EXIT_BAD_VALUE, exec->argv[1]);
			status = 255;
		}
		else
		{
			status = ft_atoi(exec->argv[1]);
			if (status > 255)
				status = status % 256;
			ft_printf("exit\n");
		}
	}
	clear_data(data);
	exit(status);
}
