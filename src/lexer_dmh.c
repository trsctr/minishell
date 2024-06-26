/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dmh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 22:24:43 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/11 16:49:18 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_dmh	*dmh_new(t_data *data, size_t size)
{
	t_dmh	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(t_dmh) * 1);
	if (!res)
		malloc_error(data);
	res->next = NULL;
	res->mem_hold = malloc(sizeof(char) * size);
	if (!res->mem_hold)
		malloc_error(data);
	return (res);
}

char	*dmh(t_data *data, size_t size)
{
	t_dmh	*tmp;

	if (data->lexer.dmh_list == NULL)
	{
		data->lexer.dmh_list = dmh_new(data, size);
		return (data->lexer.dmh_list->mem_hold);
	}
	tmp = data->lexer.dmh_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = dmh_new(data, size);
	return (tmp->next->mem_hold);
}

void	free_list_dmh(t_data *data)
{
	t_dmh	*tmp;

	while (data->lexer.dmh_list)
	{
		if (data->lexer.dmh_list->mem_hold != NULL)
			free(data->lexer.dmh_list->mem_hold);
		tmp = data->lexer.dmh_list->next;
		if (data->lexer.dmh_list != NULL)
			free(data->lexer.dmh_list);
		data->lexer.dmh_list = tmp;
	}
}
