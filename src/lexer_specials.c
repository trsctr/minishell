/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:51:54 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/07 17:15:00 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	exit_error(t_data *data, char *error)
{
	printf("%s\n", error);
	(void)data;
	exit(1);
}

void	init_data_lexer(t_data *data)
{
    data->lexer.tmp_str = NULL;
	data->lexer.exp = NULL;
	data->lexer.exp_tmp = NULL;
	data->lexer.exp_env = NULL;
	data->lexer.input_len = 0;
	data->lexer.s_quote_open = 0;
	data->lexer.d_quote_open = 0;
    data->lexer.str_open = 0;
	data->lexer.words = 0;
	data->lexer.token = NULL;
	while(data->input[data->lexer.input_len])
	{
		data->lexer.input_len++;
	}
}

int		handle_spaces(t_data *data, int i)
{
	if(data->lexer.str_open == 1)
    {
        tokenize(data, T_WORD, data->lexer.tmp_str);
        data->lexer.str_open = 0;
    }
		while(data->input[i] == ' ' || data->input[i] == '\t')
			i++;
	return (i);
}

void	free_list_token(t_data *data)
{
	t_token *tmp;
	while(data->lexer.token)
	{
		tmp = data->lexer.token->next;
		free(data->lexer.token);
        data->lexer.token = tmp;
	}
}