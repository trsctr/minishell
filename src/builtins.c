/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:54:26 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/19 18:20:23 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void builtin_cd(char *dir, t_ms *ms)
{
	// t_ev *curr;
	// char buf[200];
	(void) ms;
	// getcwd(buf, 200);
	// curr = ms->env_var;
	// while(curr && ft_strncmp(curr->content, "OLDPWD", 6))
	// 	curr = curr->next;
	// //paivita oldpwd
	// ft_memset(curr->content, 0, ft_strlen(curr->content));
	// curr->content = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(buf));
	chdir(dir);
	// getcwd(buf, 200);
	// curr = ms->env_var;
	// while(curr && ft_strncmp(curr->content, "PWD", 3))
	// 	curr = curr->next;
	// ft_memset(curr->content, 0, ft_strlen(curr->content));
	// curr->content = ft_strjoin(ft_strdup("PWD="), ft_strdup(buf));
}

void	builtin_pwd(void)
{
	char buf[200];

	getcwd(buf, 200);
	ft_printf("%s\n", buf);
}

void builtin_env (t_ms *ms)
{
	t_ev *curr;

  curr = ms->env_var;
	while (curr)
	{
    ft_printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

