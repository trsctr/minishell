/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:40:59 by slampine          #+#    #+#             */
/*   Updated: 2023/08/30 15:19:19 by slampine         ###   ########.fr       */
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

/**
 * @brief checks whether command is abs or relative path
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
 * @brief Gets command_path (e.g. /bin/ls) from environemental variable PATH
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
	ft_printf("minishell: "CMD_NOT_FOUND": %s\n", cmd);
	free_array(allpaths);
	return (NULL);
}

/**
 * @brief Create a envp object from data->env_var, envp is then given to execve
 * 
 * @param data 
 * @return char** 
 */
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

// void	old_find_n_exec(char **array, t_data *data)
// {
// 	t_ev	*path_line;
// 	char	*cmd_path;
// 	char	**envp;
// 	pid_t	pid;

// 	path_line = ft_find_var(&data->env_var, "PATH");
// 	if (!path_line)
// 	{	
// 		ft_printf("minishell: "CMD_NOT_FOUND": %s\n", array[0]);
// 		return ;
// 	}
// 	cmd_path = get_cmd_path(path_line->value, array[0]);
// 	if (cmd_path)
// 	{
// 		envp = create_envp(data);
// 		pid = fork();
// 		if (pid == 0)
// 			execve(cmd_path, array, envp);
// 		free(cmd_path);
// 		free_array(envp);
// 	}
// }
// 
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

/**
 * @brief executes the command as absolute path
 * 
 * @param data 
 * @param cmd 
 * @param cmd_path 
 */
void	exec_abs_path(t_data *data, t_exec *cmd, char *cmd_path)
{
	char	**envp;
	pid_t	pid;

	envp = create_envp(data);
	pid = fork();
	if (pid == 0)
	{
		printf("for %s write is %i and read is %i\n",cmd->cmd,cmd->pipe_out[1], cmd->pipe_in[0]);
		dup2(cmd->write_fd, cmd->pipe_out[1]);
		close(cmd->pipe_out[0]);
		dup2(cmd->read_fd, cmd->pipe_in[0]);
		close(cmd->pipe_in[1]);
		execve(cmd_path, cmd->argv, envp);
	}
	free_array(envp);
}

/**
 * @brief is given a command as relatve path, finds absolute path and uses 
 * exec_abs_path to run the command
 * 
 * @param exec 
 * @param data 
 */
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

/**
 * @brief command executor, checks if is abs or relative path, works accordingly
 * 
 * @param data 
 * @param exec 
 * @return int 
 */
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

/* runs builtin-command based on spec, spec is return of is_builin
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
