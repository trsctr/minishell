/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:54:26 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/21 18:13:00 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "env_var.h"

void	builtin_cd(char *dir, t_ms *ms)
{
	t_ev	*home;
	char	buf[200];

	getcwd(buf, 200);
	ft_change_var(&ms->env_var, "OLDPWD", buf);
	if (!dir)
	{
		home = ft_find_var(&ms->env_var, "HOME");
		dir = home->value;
	}
	chdir(dir);
	getcwd(buf, 200);
	ft_change_var(&ms->env_var, "PWD", buf);
}

void	builtin_pwd(void)
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

void builtin_export(t_ms *ms, char *arg)
{
	char	*key;
	char	*value;

	if (!arg || !ft_strchr(arg, '='))
		return ;
	else
	{	
		key = get_var_key(arg);
		value = ft_strdup(ft_strchr(arg, '=') + 1);
		if (!ft_find_var(&ms->env_var, key))
			ft_new_env_var(&ms->env_var, ft_new_evnode(key, value));
		else
		{	
			ft_change_var(&ms->env_var, key, value);
			free(key);
			free(value);
		}
	}
}

void builtin_unset (t_ms *ms, char *key)
{
	ft_delete_var(&ms->env_var, key);
}

