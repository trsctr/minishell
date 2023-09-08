/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:49:24 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/08 22:00:10 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	fill_node(t_data *data, t_token **token, int type, char *str)
{
	t_token	*new;
	t_token *tmp;

	new = malloc(sizeof(t_token) * 1);
	if (!new)
		malloc_error(data);
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
	fill_node(data, &data->lexer.token, type, str);
	data->lexer.tmp_str = NULL;
}