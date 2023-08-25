/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:40:59 by slampine          #+#    #+#             */
/*   Updated: 2023/08/25 12:54:51 by slampine         ###   ########.fr       */
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

char	**create_envp(t_ms *ms)
{
	char	**array;
	t_ev	*temp;
	int		i;

	temp = ms->env_var;
	i = 1;
	while (temp->next)
	{
		temp = temp->next;
		i++;
	}
	printf("env has %i lines\n",i);
	array = malloc(sizeof(char *) * (i + 1));
	i = 0;
	temp = ms->env_var;
	while (temp->next)
	{
		array[i] = malloc(sizeof(char) * (ft_strlen(temp->value) + 2 + ft_strlen(temp->key)));
		i++;
		temp = temp->next;
	}
	return (array);
}

void	find_n_exec(char **array, t_ms *ms)
{
	t_ev	*path_line;
	char	*cmd_path;
	pid_t	pid;

	path_line = ft_find_var(&ms->env_var, "PATH");
	if (!path_line)
	{	
		ft_printf("minishell: "CMD_NOT_FOUND": %s\n", array[0]);
		return ;
	}
	cmd_path = get_cmd_path(path_line->value, array[0]);
	if (cmd_path)
	{
		create_envp(ms);
		pid = fork();
		if (pid == 0)
			execve(cmd_path, array, NULL);
		free(cmd_path);
	}
}

int	executor(char *source, t_ms *ms)
{
	char	**array;
	pid_t	pid;

	array = ft_split(source, ' ');
	if (array == NULL)
		return (0);
	if (array[0])
	{
		if (is_abs_path(array[0]))
		{
			create_envp(ms);
			pid = fork();
			if (pid == 0)
				execve(array[0], array, NULL);
		}
		else
			find_n_exec(array, ms);
	}
	free_array(array);
	return (1);
}

/*	checks whether input is builtin, if yes, return spec, 
*	which is then given to run_builtin that 
*	runs the command
*/

int	is_builtin(char *input)
{
	if (!ft_strncmp(input, "cd", 2))
		return (1);
	else if (!ft_strncmp(input, "env", 3))
		return (2);
	else if (!ft_strncmp(input, "pwd", 3))
		return (3);
	else if (!ft_strncmp(input, "export", 6))
		return (4);
	else if (!ft_strncmp(input, "unset", 5))
		return (5);
	else if (!ft_strncmp(input, "echo", 4))
		return (6);
	return (0);
}

/* runs builtin-command based on spec
*/

void	run_builtin(char *input, int spec, t_ms *ms)
{
	char	*temp;

	if (spec == 1)
	{
		if (ft_strlen(input) > 3)
			builtin_cd(input + 3, ms);
		else
			builtin_cd(NULL, ms);
	}
	if (spec == 2)
		builtin_env(ms);
	if (spec == 3)
		builtin_pwd();
	if (spec == 4)
		builtin_export(ms, input + 7);
	if (spec == 5)
		builtin_unset(ms, input + 6);
	if (spec == 6)
	{
		temp = ft_strtrim(input + 5, " ");
		builtin_echo(temp);
		free(temp);
	}
}
