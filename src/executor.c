/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:40:59 by slampine          #+#    #+#             */
/*   Updated: 2023/09/06 15:05:22 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "env_var.h"
#include "executor.h"
#include "heredoc.h"

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
		if (!array[i])
		{
			printf("Malloc error\n");
			free_array(array);
			return (NULL);
		}
		free(temp);
		i++;
		env = env->next;
	}
	temp = ft_strjoin(env->key, "=");
	array[i] = ft_strjoin(temp, env->value);
	if (!array[i])
	{
		printf("Malloc error\n");
		free_array(array);
		return (NULL);
	}
	i++;
	free(temp);
	array[i] = NULL;
	return (array);
}

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
	if (pid == -1)
	{
		ft_printf_stderr("minishell: Pipe failed\n");
		exit (1);
	}
	if (pid == 0)
	{
		dup2(cmd->read_fd, 0);
		dup2(cmd->write_fd, 1);
		execve(cmd_path, cmd->argv, envp);
	}
	if (cmd->read_fd != 0)
		close(cmd->read_fd);
	if (cmd->write_fd != 1)
		close(cmd->write_fd);
	free_array(envp);
	waitpid(pid, NULL, 0);
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
 * @brief handles inputs redirection, returns 0 if succesful, 1 if not
 * 
 * @param exec 
 * @return int 
 */
int	handle_redir_out(t_exec *exec)
{
	int	fd_out;

	if (exec->redir_out == TRUNC_OUT)
		fd_out = open(exec->outfile, O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (exec->redir_out == APPEND_OUT)
		fd_out = open(exec->outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd_out == -1)
		return (1);
	if (exec->write_fd != 1)
		close(exec->write_fd);
	exec->write_fd = fd_out;
	return (0);
}

/**
 * @brief handles outputs redirection, returns 0 if succesful, 1 if not
 * 
 * @param exec 
 * @return int 
 */
int	handle_redir_in(t_exec *exec)
{
	int			fd_in;

	if (exec->redir_in == INPUT_FILE)
		fd_in = open(exec->infile, O_RDONLY);
	if (exec->redir_in == INPUT_HEREDOC)
	{
		fd_in = open(exec->infile, O_RDWR);
	}
	if (fd_in == -1)
		return (1);
	if  (exec->read_fd != 0)
		close(exec->read_fd);
	exec->read_fd = fd_in;
	return (0);
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
		if (exec->redir_in)
		{
			if (handle_redir_in(exec))
				return (1);
		}
		if (exec->redir_out)
		{
			if (handle_redir_out(exec))
				return (1);
		}
		if (is_abs_path(exec->cmd))
			exec_abs_path(data, exec, exec->cmd);
		else
			find_n_exec(exec, data);
	}
	exec->write_fd = 1;
	exec->read_fd = 0;
	if (exec->redir_in == 2)
	{
		/*TODO remove temp_heredocs*/
		remove(exec->infile);
	}
	return (0);
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
	if (spec == 2)
		builtin_env(data);
	if (spec == 3)
		builtin_pwd(exec);
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
