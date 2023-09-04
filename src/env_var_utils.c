/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:34:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/30 14:27:53 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_var.h"

/**
 * @brief creates new node to the environment variable linked list
 * 
 * @param key key of the variable
 * @param value value of the variable
 * @return t_ev* returns the new node
 */
t_ev	*ft_new_evnode(char *key, char *value)
{
	t_ev	*node;

	node = (t_ev *)malloc(sizeof(t_ev));
	if (!node)
		return (NULL);
	if (!key)
		node->key = NULL;
	else
		node->key = ft_strdup(key);
	if (!value)
		node->value = NULL;
	else
		node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

/**
 * @brief this function takes a new t_ev node *new_var and adds it to the
 * end of the linked list **vars
 * if the list is empty, *new_var becomes the first entry of the list
 *  
 * @param vars 
 * @param new_var 
 */
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

/**
 * @brief this function is used to find the environment variable based
 * on the keyword *key
 * 
 * @param vars env_var linked list
 * @param key environment variable key
 * @return t_ev* linked list node with the provided keyword
 * or NULL if not found
 */
t_ev	*ft_find_var(t_ev **vars, char *key)
{
	t_ev	*curr;
	size_t	keylen;

	keylen = ft_strlen(key);
	curr = *vars;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (curr);
		else
			curr = curr->next;
	}
	return (NULL);
}

/**
 * @brief deletes an environment variable from the linked list based on the
 * *key keyword
 * 
 * @param vars environment variable linked list 
 * @param key keyword of the node that needs to be deletd
 */
void	ft_delete_var(t_ev **vars, char *key)
{
	t_ev	*curr;
	t_ev	*to_remove;

	curr = *vars;
	while (curr->next && ft_strcmp(curr->next->key, key))
	{
		curr = curr->next;
	}
	if (curr->next && !ft_strcmp(curr->next->key, key))
	{
		to_remove = curr->next;
		curr->next = to_remove->next;
		free(to_remove->key);
		free(to_remove->value);
		free(to_remove);
	}
}

/**
 * @brief updates the value of an environment variable
 * doesn't do anything if there's no variable with the key *key
 * @param vars env_var linked list
 * @param key key of the variable
 * @param value new value
 */
void	ft_change_var(t_ev **vars, char *key, char *value)
{
	t_ev	*change;

	change = ft_find_var(vars, key);
	if (!change)
		return ;
	else
		free(change->value);
	change->value = ft_strdup(value);
}

/**
 * @brief deletes and frees the linked list so we can exit gracefully
 * 
 * @param ms 
 */
void	ft_clear_evlist(t_data *data)
{
	t_ev	*temp;

	temp = data->env_var;
	while (temp)
	{
		free(temp->key);
		free(temp->value);
		free(temp);
		temp = temp->next;
	}
}
