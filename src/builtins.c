/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:54:26 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/25 12:28:39 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "env_var.h"

void	builtin_cd(char *dir, t_ms *ms)
{
	t_ev	*home;
	char	buf[200];
	char	*temp;

	getcwd(buf, 200);
	ft_change_var(&ms->env_var, "OLDPWD", buf);
	if (!dir)
	{
		home = ft_find_var(&ms->env_var, "HOME");
		if (!home)
		{
			ft_printf("cd : HOME not set\n");
			return ;
		}
		dir = home->value;
	}
	temp = ft_strtrim(dir, " ");
	dir = temp;
	free (temp);
	if (chdir(dir) != 0)
		perror("");
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

void	builtin_export(t_ms *ms, char *arg)
{
	char	*key;

	if (!arg || !ft_strchr(arg, '='))
		return ;
	else
	{	
		key = get_var_key(arg);
		if (!ft_find_var(&ms->env_var, key))
			ft_new_env_var(&ms->env_var, ft_new_evnode(ft_strdup(key), ft_strdup(ft_strchr(arg, '=') + 1)));
		else
			ft_change_var(&ms->env_var, key, ft_strchr(arg, '=') + 1);
	}
}

void	builtin_unset(t_ms *ms, char *key)
{
	ft_delete_var(&ms->env_var, key);
}

void	builtin_echo(char *src)
{
	if (!ft_strnstr(src, "-n", 3))
	{
		ft_putstr_fd(src, 1);
		ft_putchar_fd('\n', 1);
	}
	else
		ft_putstr_fd(src + 3, 1);
}
