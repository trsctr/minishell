/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:58:41 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/14 12:11:52 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_var.h"
/**
 * @brief if cd is success (ie the given dir is valid)
 * this function updates environment variables for
 * 
 * @param data 
 * @param oldpwd 
 */
static void	cd_success(t_data *data, char *oldpwd)
{
	char	*newpwd;

	ft_change_var(&data->env_var, "OLDPWD", oldpwd);
	newpwd = getcwd(NULL, 0);
	ft_change_var(&data->env_var, "PWD", newpwd);
	free(newpwd);
	set_exit_status(data, 0);
}

/**
 * @brief builtin "cd" command which changes the current working directory
 * also updates OLDPWD and PWD in the env_vars 
 * goes to users home directory if there are no args, but displays an error 
 * message if $HOME env var is not set
 * if given directory does not exist, an error message is displayed and
 * no env vars are updated
 * 
 * @param data 
 * @param exec 
 */
void	builtin_cd(t_data *data, t_exec *exec)
{
	t_ev	*home;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!exec->argv[1])
	{
		free(exec->argv[0]);
		free(exec->argv);
		exec->argv = ft_calloc(3, sizeof(char *));
		exec->argv[0] = ft_strdup("cd");
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
		cd_success(data, oldpwd);
	else
	{
		perror(exec->argv[1]);
		set_exit_status(data, 1);
	}
	free(oldpwd);
}
