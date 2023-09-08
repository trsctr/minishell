/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:54:59 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/08 19:20:58 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief this function is a helper function for builtin_export
 * key can contain alphanumeric characters and underscores
 * but can't start with a digit
 * 
 * @param key 
 * @return int returns 1 if key is valid, 0 if not.
 */
int	key_is_valid(char *key)
{
	int	i;

	i = 0;
	if (key[0] == '\0' || ft_isdigit(key[0]))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void export_print_vars(t_ev **vars, int fd)
{
	t_ev	*curr;

	curr = *vars;
	while (curr)
	{
		ft_dprintf(fd, "declare -x %s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}
