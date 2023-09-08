/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dmh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 22:24:43 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/06 23:31:10 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_dmh	*dmh_new(size_t size)
{
	t_dmh	*res;
	int i;

	i = 0;
	res = malloc(sizeof(t_dmh) * 1);
	if(!res)
		return(NULL);
	res->next = NULL;
	res->mem_hold = malloc(sizeof(char) * size);
	if(!res->mem_hold)
		return(NULL);
	return(res);
}

char	*dmh(t_data *data, size_t size)
{
	t_dmh *tmp;
	
	if(data->lexer.dmh_list == NULL)
	{
		data->lexer.dmh_list = dmh_new(size);
		return(data->lexer.dmh_list->mem_hold);
	}
	tmp = data->lexer.dmh_list;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = dmh_new(size);
	return(tmp->next->mem_hold);
}

void	free_list_dmh(t_data *data)
{
	t_dmh *tmp;
	while(data->lexer.dmh_list)
	{
		free(data->lexer.dmh_list->mem_hold);
		tmp = data->lexer.dmh_list->next;
		free(data->lexer.dmh_list);
        data->lexer.dmh_list = tmp;
	}
}