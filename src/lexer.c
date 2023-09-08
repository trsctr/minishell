/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:45 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/08 22:00:16 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	if(data->input[i] == '\'' || data->input[i] == '\"')
	{
		i = handle_quotes(data, i);
		return (i);
	}
	if((data->input[i] == ' ' || data->input[i] == '\t'))
	{
        i = handle_spaces(data, i);
		return (i);
	}
	i = handle_pipes_redirects(data, i);
	return (i);
}

void	lexer(t_data *data)
{
	int i;

	i = 0;
	init_data_lexer(data);
	while(data->input[i] && data->lexer.syntax_error == 0)
	{
        if(data->input[i] == '\'' || data->input[i] == '\"'
		|| data->input[i] == ' ' || data->input[i] == '\t'
		|| data->input[i] == '>' || data->input[i] == '<'
		|| data->input[i] == '|')
		{
			i = handle_specials(data, i);
			continue;
		}
		i = handle_words_unquoted(data, i);
	}
	if(data->lexer.syntax_error == 0)
	{
		if(data->lexer.str_open == 1 && data->lexer.tmp_str[0] != '\0')
			tokenize(data, T_WORD, data->lexer.tmp_str);
		check_token(data);
	}
}

// Kysy getenv asia liittyen executable ja expandable testiin etta voiko kayttaa jos env_var lista paivitetty minishellin sisalla etta pitaako kayttaa jotain omaa

// malloc errorit -> miten tehdaan jos malloc failaa mutta ei exittaa niin koittaa kayttaa rikkinaisia pointtereita niin kauan kuin ohjelma tulee loppuun

// muuta enum errorit

// CMD check

// lohkon sisalla ei voi olla kuin yksi CMD

	// lohkon eka pitaa olla RD tai CMD
	
		// jos RD niin seuraava on WORD ja siita seuraava WORD = CMD	|esim|	> file echo

		// jos CMD niin siita kaikki seuraavat WORDit WORDeja			|esim|	echo jee joo juu > file

// special case	|esim|	> file echo < file2 cat -> syntax error koska RD kanssa aina vain yksi WORD joten tassa tapauksessa "echo" on CMD ja cat lopussa ei ole mitaan koska tokalla RDlla on jo WORD "file2"

