/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pipes_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:47:42 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/11 16:37:56 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	redirect_solver(t_data *data, int i)
{
	int	j;

	j = i;
	while (data->input[j] == '>' || data->input[j] == '<')
		j++;
	if (j - i > 2 || (j - i == 2 && data->input[i] != data->input[i + 1]))
	{
		data->lexer.syntax_error = 1;
		return (i);
	}
	if (j - i == 1 && data->input[i] == '<')
		tokenize(data, T_RD_S_L, "<");
	if (j - i == 1 && data->input[i] == '>')
		tokenize(data, T_RD_S_R, ">");
	if (j - i == 2 && data->input[i] == '<')
		tokenize(data, T_RD_D_L, "<<");
	if (j - i == 2 && data->input[i] == '>')
		tokenize(data, T_RD_D_R, ">>");
	return (j);
}

int	handle_pipes_redirects(t_data *data, int i)
{
	int	j;

	j = i;
	if (data->lexer.str_open == 1)
	{
		tokenize(data, T_WORD, data->lexer.tmp_str);
		data->lexer.str_open = 0;
	}
	if (data->input[i] == '>' || data->input[i] == '<')
	{
		i = redirect_solver(data, i);
		return (i);
	}
	if (data->input[i + 1] == '|')
		data->lexer.syntax_error = 1;
	tokenize(data, T_PIPE, "|");
	return (i + 1);
}
