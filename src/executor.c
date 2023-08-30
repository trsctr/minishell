/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:40:59 by slampine          #+#    #+#             */
/*   Updated: 2023/08/25 16:17:43 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "env_var.h"
#include "executor.h"

int	is_abs_path(char *src)
{
	if (access(src, X_OK) == 0)
		return (1);
	return (0);
}

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
	ft_printf("minishell: "CMD_NOT_FOUND": %s\n", cmd);
	free_array(allpaths);
	return (NULL);
}


char	**create_envp(t_data *data)
{
	char	**array;
	t_ev	*temp;
	int		i;

	temp = data->env_var;
	i = 1;
	while (temp->next)
	{
		temp = temp->next;
		i++;
	}
	array = malloc(sizeof(char *) * (i + 1));
	i = 0;
	temp = data->env_var;
	while (temp->next)
	{
		array[i] = ft_strjoin(temp->key, "=");
		array[i] = ft_strjoin(array[i], temp->value);
		i++;
		temp = temp->next;
	}
	return (array);
}

void	find_n_exec(char **array, t_data *data)
{
	t_ev	*path_line;
	char	*cmd_path;
	pid_t	pid;
	char	**envp;

	envp = NULL;
	path_line = ft_find_var(&data->env_var, "PATH");
	if (!path_line)
	{	
		ft_printf("minishell: "CMD_NOT_FOUND": %s\n", array[0]);
		return ;
	}
	cmd_path = get_cmd_path(path_line->value, array[0]);
	if (cmd_path)
	{
		envp = create_envp(data);
		pid = fork();
		if (pid == 0)
			execve(cmd_path, array, envp);
		free(cmd_path);
		free(envp);
	}
}

int	executor(t_exec *exec, t_data *data)
{
	char	**envp;
	pid_t	pid;

	envp = NULL;
	if (is_abs_path(exec->cmd))
	{
			envp = create_envp(data);
			pid = fork();
			if (pid == 0)
				execve(exec->cmd, exec->argv, envp);
	}
	else
			find_n_exec(exec->argv, data);
	if (envp)
		free_array(envp);
	return (1);
}

/*	checks whether input is builtin, if yes, return spec, 
*	which is then given to run_builtin that 
*	runs the command
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
	return (0);
}

/* runs builtin-command based on spec
*/

void	run_builtin(t_exec *exec, int spec, t_data *data)
{

	if (spec == 1)
		builtin_cd(data, exec);
	if (spec == 2)
		builtin_env(data);
	if (spec == 3)
		builtin_pwd();
	if (spec == 4)
		builtin_export(data, exec);
	if (spec == 5)
		builtin_unset(data, exec);
	if (spec == 6)
	{
		builtin_echo(data, exec);// temp = ft_strtrim(input + 5, " ");
		// builtin_echo(temp);
		// free(temp);
	}
}
