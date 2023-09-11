/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:49:06 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/11 17:19:38 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "prompt.h"

void	malloc_error(t_data *data)
{
	ft_errormsg(MALLOC_FAIL, NULL);
	terminal_reset(data);
	clear_data(data);
	free_list_dmh(data);
	if (data->lexer.token != NULL)
		free_list_token(data);
	exit(1);
}

void	clear_data(t_data *data)
{
	clear_history();
	ft_clear_evlist(data);
	if (data)
		free(data);
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
