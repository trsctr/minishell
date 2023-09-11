/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:45:21 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/11 16:11:09 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_words_unquoted(t_data *data, int i)
{
	int	start;

	start = i;
	while (data->input[i] != '\'' && data->input[i] != '\"'
		&& data->input[i] != ' ' && data->input[i] != '\t'
		&& data->input[i] != '|' && data->input[i] != '>'
		&& data->input[i] != '<' && data->input[i] != '\0')
		i++;
	data->lexer.str_open = 1;
	check_expandable(data, start, i - start);
	if (data->lexer.tmp_str == NULL)
		data->lexer.tmp_str = ft_strdup_dmh(data, data->lexer.exp);
	else
		data->lexer.tmp_str = ft_strjoin_dmh(data,
				data->lexer.tmp_str, data->lexer.exp);
	return (i);
}

int	handle_words_d_quoted(t_data *data, int i)
{
	int	start;

	start = i;
	while (data->input[i] != quote_status(data))
	{
		if (!data->input[i])
		{
			data->lexer.syntax_error = 1;
			return (i);
		}
		i++;
	}
	data->lexer.str_open = 1;
	check_expandable(data, start, i - start);
	if (data->lexer.tmp_str == NULL)
		data->lexer.tmp_str = ft_strdup_dmh(data, data->lexer.exp);
	else
		data->lexer.tmp_str = ft_strjoin_dmh(data,
				data->lexer.tmp_str, data->lexer.exp);
	open_close_quotes(data, data->input[i]);
	return (i + 1);
}

int	handle_words_s_quoted(t_data *data, int i)
{
	int	start;

	start = i;
	while (data->input[i] != quote_status(data))
	{
		if (!data->input[i])
		{
			data->lexer.syntax_error = 1;
			return (i);
		}
		i++;
	}
	data->lexer.str_open = 1;
	if (data->lexer.tmp_str == NULL)
		data->lexer.tmp_str
			= ft_strndup_dmh(data, data->input + start, i - start);
	else
		data->lexer.tmp_str = ft_strjoin_dmh(data, data->lexer.tmp_str,
				ft_strndup_dmh(data, data->input + start, i - start));
	open_close_quotes(data, data->input[i]);
	return (i + 1);
}

int	handle_quotes(t_data *data, int i)
{
	if (empty_word(data, i) && !quote_status(data))
	{
		tokenize(data, T_EMPTY_WORD, ft_strndup_dmh(data,
				data->input + i, empty_word(data, i)));
		return (i + empty_word(data, i));
	}
	else if (data->input[i] == data->input[i + 1])
		return (i + 2);
	else
	{
		open_close_quotes(data, data->input[i]);
		if (data->input[i] == '\'')
			return (handle_words_s_quoted(data, i + 1));
		else
			return (handle_words_d_quoted(data, i + 1));
	}
}
