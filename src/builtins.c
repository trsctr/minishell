/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:54:26 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/11 14:31:33 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "env_var.h"
#include "prompt.h"

/**
 * @brief builtin "cd" command which changes the current working directory
 * also updates OLDPWD and PWD in the env_vars 
 * goes to users home directory if there are no args, but displays an error message
 * if $HOME env var is not set
 * if given directory does not exist, an error message is displayed and no env vars
 * are updated
 * 
 * @param data 
 * @param exec 
 */
void	builtin_cd(t_data *data, t_exec *exec)
{
	t_ev	*home;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!exec->argv[1])
	{
		home = ft_find_var(&data->env_var, "HOME");
		if (!home)
		{
			ft_printf("cd : HOME not set\n");
			set_exit_status(data, 1);
			return ;
		}
		exec->argv[1] = ft_strdup(home->value);
	}
	if (!chdir(exec->argv[1]))
	{
		ft_change_var(&data->env_var, "OLDPWD", oldpwd);
		newpwd = getcwd(NULL, 0);
		ft_change_var(&data->env_var, "PWD", newpwd);
		free(newpwd);
		set_exit_status(data, 0);
	}
	else
	{
		perror(exec->argv[1]);
		set_exit_status(data, 1);
	}
	free(oldpwd);
}

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
 * @brief builtin export command, saves new environment variables
 * as long as they are given in format key=value
 * if an env var exists with the given key, then the value is updated
 * 
 * @param data 
 * @param exec 
 */
void	builtin_export(t_data *data, t_exec *exec)
{
	char	*key;
	char	*value;
	int		i;
	int		error;

	error = 0;
	i = 1;
	if (!exec->argv[i])
		export_print_vars(&data->env_var, exec->write_fd);
	else
	{
		while (exec->argv[i])
		{
			if (!ft_strchr(exec->argv[i], '='))
			{
				i++;
				continue ;
			}
			key = get_ev_key(exec->argv[i]);
			if (!key_is_valid(key))
			{
				ft_dprintf(2, "minishell: export: '%s' not a valid identifier\n",
					exec->argv[i]);
				free(key);
				error = 1;
				i++;
				continue ;
			}
			value = get_ev_value(exec->argv[i]);
			if (!ft_find_var(&data->env_var, key))
				ft_new_env_var(&data->env_var, ft_new_evnode(key, value));
			else
				ft_change_var(&data->env_var, key, value);
			free(key);
			free(value);
			i++;
		}
	}
	set_exit_status(data, error);
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
	int error;
	
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
