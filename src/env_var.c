/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:55:03 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/19 15:34:45 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	save_env_var(char **env, t_ms *ms)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back(&ms->env_var, ft_lstnew(ft_strdup(env[i])));
		i++;
	}
	// muista paivittaa tahan oikea shelli!
}
