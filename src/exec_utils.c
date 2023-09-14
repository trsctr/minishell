/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:12:38 by slampine          #+#    #+#             */
/*   Updated: 2023/09/14 12:02:21 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "env_var.h"
#include "executor.h"
#include "heredoc.h"

int	cmd_is_dir(t_data *data, t_exec *exec)
{
	(void) data;
	if (!ft_strcmp(exec->cmd, "/home")
		|| !ft_strcmp(exec->cmd, "/bin")
		|| !ft_strcmp(exec->cmd, "/"))
	{
		ft_errormsg(CMD_IS_DIR, exec->cmd);
		return (1);
	}
	else
		return (0);
}

/**
 * @brief checks using access() whether command is abs or relative path
 * 
 * @param src 
 * @return int 
 */
int	is_abs_path(char *src)
{
	if (access(src, X_OK) == 0)
		return (1);
	return (0);
}

/**
 * @brief Gets command_path (e.g. /bin/ls) from environmental variable PATH
 * 
 * @param path_line 
 * @param cmd 
 * @return char* 
 */
char	*get_cmd_path(char *path_line, char *cmd)
{
	char	*temp;
	char	*cmd_path;
	char	**allpaths;
	int		i;

	allpaths = ft_split(path_line, ':');
	i = 0;
	while (allpaths[i])
	{
		temp = ft_strjoin(allpaths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(allpaths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(allpaths);
	return (NULL);
}

/**
 * @brief check whether command is builtin or not
 * if yes, returns spec (>0), which is given to 
 * run_builtin if no, returns 0
 * 
 * @param cmd 
 * @return int 
 */
int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (2);
	else if (!ft_strcmp(cmd, "pwd"))
		return (3);
	else if (!ft_strcmp(cmd, "export"))
		return (4);
	else if (!ft_strcmp(cmd, "unset"))
		return (5);
	else if (!ft_strcmp(cmd, "echo"))
		return (6);
	else if (!ft_strcmp(cmd, "exit"))
		return (7);
	return (0);
}

/**
 * @brief runs builtin-command based on spec, spec is return of is_builin
 * 
 * @param exec 
 * @param spec 
 * @param data 
 */
void	run_builtin(t_exec *exec, int spec, t_data *data)
{
	if (spec == 1)
		builtin_cd(data, exec);
	else if (spec == 2)
		builtin_env(data, exec);
	else if (spec == 3)
		builtin_pwd(data, exec);
	else if (spec == 4)
		builtin_export(data, exec);
	else if (spec == 5)
		builtin_unset(data, exec);
	else if (spec == 6)
		builtin_echo(data, exec);
	else if (spec == 7)
		builtin_exit(data, exec);
}