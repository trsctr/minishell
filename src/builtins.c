/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:54:26 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/25 14:22:21 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "env_var.h"

void	builtin_cd(t_data *data, t_exec *exec)
{
	t_ev	*home;
	char	buf[200];
	int		status;
	// char	*temp;

	getcwd(buf, 200);
	ft_change_var(&data->env_var, "OLDPWD", buf);
	if (!exec->argv[1])
	{
		home = ft_find_var(&data->env_var, "HOME");
		if (!home)
		{
			ft_printf("cd : HOME not set\n");
			return ;
		}
		chdir(home->value);
	}
	else 
		status = chdir(exec->argv[1]);
	if (!status)
	{
		getcwd(buf, 200);
		ft_change_var(&data->env_var, "PWD", buf);
	}
	else
		perror("");
}


void	builtin_pwd(void)
{
	char	buf[200];

	getcwd(buf, 200);
	ft_printf("%s\n", buf);
}

void	builtin_env(t_data *data)
{
	t_ev	*curr;

	curr = data->env_var;
	while (curr)
	{
		ft_printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

void	builtin_export(t_data *data, t_exec *exec)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	if (!exec->argv[i])
		return ;
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
			if (key[0] == '\0')
			{
				free(key);
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
}

void	builtin_unset(t_data *data, t_exec *exec)
{
	int	i;

	i = 1;
	while (exec->argv[i])
	{
		ft_delete_var(&data->env_var, exec->argv[i]);
		i++;
	}
}

// void	builtin_echo(char *src)
// {
// 	if (!ft_strnstr(src, "-n", 3))
// 	{
// 		ft_putstr_fd(src, 1);
// 		ft_putchar_fd('\n', 1);
// 	}
// 	else
// 		ft_putstr_fd(src + 3, 1);
// }
