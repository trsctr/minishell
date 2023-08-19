/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:54:26 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/19 15:47:27 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void builtin_cd(char *dir, t_ms *ms)
{
	//paivita oldpwd
	(void) dir;
	(void) ms;
}

void	builtin_pwd(void)
{
	char buf[200];

	getcwd(buf, 200);
	ft_printf("%s\n", buf);
}
void builtin_env(t_ms *ms)
{
	t_list *curr;

	curr = ms->env_var;
	while (curr)
	{
		ft_printf("%s\n", curr->content);
		curr = curr->next;
	}
}

