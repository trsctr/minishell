/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:55:03 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/19 18:45:43 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "env_var.h"

void	save_env_var(char **env, t_ms *ms)
{
	int	i;
	char *key;

	i = 0;
	while (env[i])
	{
		key = get_var_key(env[i]);
		// teet nyt tasta vitusti paremman
		ft_new_env_var(&ms->env_var, ft_new_evnode(ft_strdup(key), ft_strdup(ft_strchr(env[i], '=') + 1)));
		free(key);
		i++;
	}
	// muista paivittaa tahan oikea shelli!
}

char *get_var_key(char *str)
{
	int len;
	char *key;
	
	len = 0;
	while (str[len] != '=')
		len++;
	len++;
	key = malloc(sizeof(char) * len);
	ft_strlcpy(key, str, len);
	return(key);
}

t_ev *ft_new_evnode(char *key, char *value)
{
	t_ev	*node;

	node = (t_ev *)malloc(sizeof(t_ev));
	if (!node)
		return (NULL);
	if (!key)
		node->key = NULL;
	else
		node->key = key;
	if (!value)
		node->value = NULL;
	else
		node->value = value;
	node->next = NULL;
	return (node);
}

void	ft_new_env_var(t_ev **vars, t_ev *new_var)
{
	t_ev	*curr;

	curr = *vars;
	if (!*vars)
		*vars = new_var;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new_var;
	}
}