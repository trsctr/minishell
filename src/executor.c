/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:40:59 by slampine          #+#    #+#             */
/*   Updated: 2023/08/30 14:08:18 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "env_var.h"
#include "executor.h"

void	output_trunc(char *file, char *src)
{
	int	outfile;
	int	saved_out;

	outfile = open(file, O_TRUNC | O_CREAT | O_RDWR, 0777);
	saved_out = dup(1);
	dup2(outfile, 1);
	printf("%s\n", src);
	dup2(saved_out, 1);
	close(saved_out);
}

void	output_add(char *file, char *src)
{
	int	outfile;
	int	saved_out;

	outfile = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
	saved_out = dup(1);
	dup2(outfile, 1);
	printf("%s\n", src);
	dup2(saved_out, 1);
	close(saved_out);
}

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
	char	*temp;
	t_ev	*env;
	int		i;

	env = data->env_var;
	array = malloc(sizeof(char *) * (ft_envsize(data->env_var) + 1));
	i = 0;
	env = data->env_var;
	while (env->next)
	{
		temp = ft_strjoin(env->key, "=");
		array[i] = ft_strjoin(temp, env->value);
		free(temp);
		i++;
		env = env->next;
	}
	temp = ft_strjoin(env->key, "=");
	array[i] = ft_strjoin(temp, env->value);
	i++;
	free(temp);
	array[i] = NULL;
	return (array);
}

void	old_find_n_exec(char **array, t_data *data)
{
	t_ev	*path_line;
	char	*cmd_path;
	char	**envp;
	pid_t	pid;
	
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
		free_array(envp);
	}
}

// int	old_executor(char *source, t_data *data)
// {
// 	char	**array;
// 	char	**envp;
// 	pid_t	pid;

// 	envp = NULL;
// 	if (is_abs_path(exec->cmd))
// 	{
// 		if (is_abs_path(array[0]))
// 		{
// 			envp = create_envp(data);
// 			pid = fork();
// 			if (pid == 0)
// 				execve(array[0], array, envp);
// 			free_array(envp);
// 		}
// 		else
// 			old_find_n_exec(array, data);
// 	}
// 	else
// 			find_n_exec(exec->argv, data);
// 	if (envp)
// 		free_array(envp);
// 	return (1);
// }

void exec_abs_path(t_data *data, t_exec *cmd, char *cmd_path)
{
	char	**envp;
	pid_t	pid;
	
	envp = create_envp(data);
	pid = fork();
	if (pid == 0)
	{
		dup2(cmd->write_fd, 1);
		dup2(cmd->read_fd, 0);
		execve(cmd_path, cmd->argv, envp);
	}
	free_array(envp);
}

void	find_n_exec(t_exec *exec, t_data *data)
{
	t_ev	*path_line;
	char	*cmd_path;

	path_line = ft_find_var(&data->env_var, "PATH");
	if (!path_line)
	{	
		ft_printf("minishell: "CMD_NOT_FOUND": %s\n", exec->cmd);
		return ;
	}
	cmd_path = get_cmd_path(path_line->value, exec->cmd);
	if (cmd_path)
	{
		exec_abs_path(data, exec, cmd_path);
		free(cmd_path);
	}
}

int	executor(t_data *data, t_exec *exec)
{

	if (exec->argv[0])
	{
		if (is_abs_path(exec->cmd))
			exec_abs_path(data, exec, exec->cmd);
		else
			find_n_exec(exec, data);
	}
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
		builtin_echo(exec);// temp = ft_strtrim(input + 5, " ");
		// builtin_echo(temp);
		// free(temp);
	}
}
