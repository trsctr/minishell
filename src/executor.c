/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:40:59 by slampine          #+#    #+#             */
/*   Updated: 2023/09/18 17:57:11 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	array = ft_calloc(sizeof(char *), (ft_envsize(data->env_var) + 1));
	i = 0;
	env = data->env_var;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		array[i] = ft_strjoin(temp, env->value);
		if (!array[i])
		{
			ft_errormsg(MALLOC_FAIL, NULL);
			free_array(array);
			return (NULL);
		}
		free(temp);
		i++;
		env = env->next;
	}
	return (array);
}

int	child(t_data *data, t_exec *cmd, char *cmd_path, char **envp)
{
	if (cmd->write_fd == -1 || cmd->read_fd == -1)
		exit (0);
	dup2(cmd->read_fd, 0);
	dup2(cmd->write_fd, 1);
	close_pipes(data);
	reset_signals();
	if (execve(cmd_path, cmd->argv, envp))
	{
		ft_errormsg(EXEC_FAIL, cmd->argv[0]);
		close(cmd->read_fd);
		close(cmd->write_fd);
		exit(126);
	}
	return (0);
}

/**
 * @brief executes the command, requires absolute path
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
	sigemptyset(&(data->sa.sa_mask));
	data->sa.sa_sigaction = &handle_sig_in_exec;
	sigaction(SIGINT, &(data->sa), NULL);
	pid = fork();
	if (pid == -1)
	{
		ft_errormsg(PIPE_FAIL, NULL);
		set_exit_status(data, 1);
		exit (1);
	}
	if (pid == 0)
		child(data, cmd, cmd_path, envp);
	cmd->pid = pid;
	if (cmd->read_fd > 2)
		close(cmd->read_fd);
	if (cmd->write_fd > 2)
		close(cmd->write_fd);
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
		ft_errormsg(BAD_CMD, exec->cmd);
		set_exit_status(data, 127);
		return ;
	}
	cmd_path = get_cmd_path(path_line->value, exec->cmd);
	if (!cmd_path)
	{
		if (exec->read_fd > 2)
			close(exec->read_fd);
		if (exec->write_fd > 2)
			close(exec->write_fd);
		ft_errormsg(BAD_CMD, exec->cmd);
		set_exit_status(data, 127);
	}
	else
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
		if (cmd_is_dir(exec))
			set_exit_status(data, 126);
		else if ((ft_strncmp(exec->cmd, "./", 2) == 0 && is_abs_path(exec->cmd))
			|| (ft_strchr(exec->cmd, '/') && is_abs_path(exec->cmd)))
			exec_abs_path(data, exec, exec->cmd);
		else
			find_n_exec(exec, data);
	}
	if (exec->has_heredoc)
		close (exec->read_fd);
	exec->write_fd = 1;
	exec->read_fd = 0;
	return (0);
}
