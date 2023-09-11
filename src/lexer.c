/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:45 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/11 17:36:34 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*	*lexer:
*	Splits given input into words to char**.
*	Word separation is done by space or looking for second quote (" or ') 
*	after first one, if they aren't located already between quotes.
*	Also valid redirects (>, <, >>, <<) and pipe (|) will separate words (even
*	if they aren't separated by space) unless they are located between quotes.
*	Empty words ("" or '') are tokenized in their respective type.
*	Expandable variables are checked and expanded if needed (unless they're
*	located between single quotes). Words are checked if they are commands
*	and are tokenized as commands.
*/

int	handle_specials(t_data *data, int i)
{
	if (data->input[i] == '\'' || data->input[i] == '\"')
	{
		i = handle_quotes(data, i);
		return (i);
	}
	if ((data->input[i] == ' ' || data->input[i] == '\t'))
	{
		i = handle_spaces(data, i);
		return (i);
	}
	i = handle_pipes_redirects(data, i);
	return (i);
}

void	lexer(t_data *data)
{
	int	i;

	i = 0;
	init_data_lexer(data);
	while (data->input[i] && data->lexer.syntax_error == 0)
	{
		if (data->input[i] == '\'' || data->input[i] == '\"'
			|| data->input[i] == ' ' || data->input[i] == '\t'
			|| data->input[i] == '>' || data->input[i] == '<'
			|| data->input[i] == '|')
		{
			i = handle_specials(data, i);
			continue ;
		}
		i = handle_words_unquoted(data, i);
	}
	if (data->lexer.syntax_error == 0)
	{
		if (data->lexer.str_open == 1 && data->lexer.tmp_str[0] != '\0')
			tokenize(data, T_WORD, data->lexer.tmp_str);
		check_token(data);
	}
}
