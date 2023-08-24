/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:54:26 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/24 15:53:53 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "env_var.h"

void	builtin_cd(t_ms *ms, t_cmd *cmd)
{
	t_ev	*home;
	char	buf[200];

	getcwd(buf, 200);
	ft_change_var(&ms->env_var, "OLDPWD", buf);
	if (cmd->argcount == 0)
	{
		home = ft_find_var(&ms->env_var, "HOME");
		if (!home)
		{
			ft_printf("cd : HOME not set\n");
			return ;
		}
		chdir(home->value);
	}
	else
		chdir(cmd->arg[0]);
	getcwd(buf, 200);
	ft_change_var(&ms->env_var, "PWD", buf);
}

void	builtin_pwd(t_cmd *cmd)
{
	char	buf[200];

	getcwd(buf, 200);
	ft_printf("%s\n", buf);
}

void	builtin_env(t_ms *ms)
{
	t_ev	*curr;

	curr = ms->env_var;
	while (curr)
	{
		ft_printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

void	builtin_export(t_ms *ms, t_cmd *cmd)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (cmd->argcount < 1)
		return ;
	else
	{	
		while (i < cmd->argcount)
		{
			ft_printf("%s\n", cmd->arg[i]);
			if (!ft_strchr(cmd->arg[i], '='))
			{
				i++;
				continue ;
			}
			key = get_ev_key(cmd->arg[i]);
			if (key[0] == '\0')
			{
				free(key);
				i++;
				continue ;
			}
			value = get_ev_value(cmd->arg[i]);
			if (!ft_find_var(&ms->env_var, key))
				ft_new_env_var(&ms->env_var, ft_new_evnode(key, value));
			else
				ft_change_var(&ms->env_var, key, value);
			free(key);
			free(value);
			i++;
		}
	}
}

void	builtin_unset(t_ms *ms, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->argcount)
	{
		ft_delete_var(&ms->env_var, cmd->arg[i]);
		i++;
	}
}

