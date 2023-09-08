/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:49:24 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/06 23:20:45 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	fill_node(t_token **token, int type, char *str)
{
	t_token	*new;
	t_token *tmp;

	new = malloc(sizeof(t_token) * 1);
	if (!new)
		exit_error(NULL, "malloc error\n");			// kayta oikeaa exit error
	new->type = type;
	new->str = str;
	new->next = NULL;
	if (*token == NULL)
		*token = new;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	tokenize(t_data *data, int type, char *str)
{
	if(type == T_WORD && check_executable(data, str))
		type = T_CMD;
	fill_node(&data->lexer.token, type, str);
	data->lexer.tmp_str = NULL;
}