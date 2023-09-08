/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_words_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:54:45 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/06 18:59:12 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	quote_status(t_data *data)
{
	if (data->lexer.s_quote_open == 1)
		return ('\'');
	else if(data->lexer.d_quote_open == 1)
		return ('\"');
	else
		return (0);
}

void	open_close_quotes(t_data *data, char c)
{
	if (c == '\'' && data->lexer.d_quote_open == 0)
	{
		if (data->lexer.s_quote_open == 1)
			data->lexer.s_quote_open = 0;
		else
			data->lexer.s_quote_open = 1;
	}
	if (c == '\"' && data->lexer.s_quote_open == 0)
	{
		if (data->lexer.d_quote_open == 1)
			data->lexer.d_quote_open = 0;
		else
			data->lexer.d_quote_open = 1;
	}
}

int	empty_word(t_data *data, int i)
{
    int count;
	
	count = 0;
	if (data->lexer.input_len - i > 1
	    && (data->input[i] == '\'' || data->input[i] == '\"'))
    {
        if (i != 0 && data->input[i - 1] != ' ' && data->input[i - 1] != '\t')
            return (0);
        while (data->input[i] == '\'' || data->input[i] == '\"')
		{
			if (data->input[i + 1] == data->input[i])
			{
				i += 2;
				count += 2;
			}
			else
				return (0);
		}
        if (data->input[i] == '\0' || data->input[i] == ' ')
			return (count);
    }
    return (0);
}