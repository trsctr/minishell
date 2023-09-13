/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:49:06 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/13 22:38:43 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "prompt.h"
#include "utils.h"

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
	// if (data->exec)
	// 	free_exec(data->exec);
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
	t_ev	*var;
	
	var = data->env_var;
	while (var)
	{
		free(var->key);
		free(var->value);
		temp = var->next;
		free(var);
		var = temp;
	}
}
