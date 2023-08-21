/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:55:03 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/21 13:37:17 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "builtins.h"
#include "env_var.h"

/**
 * @brief saves environment variables to a linked list inside the ms struct
 * 
 * @param env 
 * @param ms 
 */
void	save_env_var(char **env, t_ms *ms)
{
	int	i;
	char *key;
	//char *value;
	
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
	return (key);
}

t_ev	*ft_new_evnode(char *key, char *value)
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

t_ev	*ft_find_var(t_ev **vars, char *key)
{
	t_ev *curr;
	size_t keylen;

	keylen = ft_strlen(key);
	curr = *vars;
	while(curr)
	{
		if (!ft_strncmp(curr->key, key, keylen))
			return(curr);
		else
			curr = curr->next;
	}
	return (NULL);
}

void	ft_delete_var(t_ev **vars, char *key)
{
	t_ev *curr;
	t_ev *to_remove;
	size_t keylen;

	keylen = ft_strlen(key);
	curr = *vars;
	while(curr->next && ft_strncmp(curr->next->key, key, keylen))
	{
		curr = curr->next;
	}
	if (!ft_strncmp(curr->next->key, key, keylen))
	{
		to_remove = curr->next;
		curr->next = to_remove->next;
		free(to_remove->key);
		free(to_remove->value);
		free(to_remove);
	}
}