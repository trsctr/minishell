/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:49:06 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/11 14:49:03 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(t_data *data)
{
	ft_errormsg(MALLOC_FAIL, NULL);
	clear_data(data);
	exit(1);
}

void	clear_data(t_data *data)
{
	ft_clear_evlist(data);
	clear_history();
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
