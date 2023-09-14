/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:51:54 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/14 16:41:20 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_syntax(t_data *data)
{
	if (data->lexer.syntax_error == 1)
	{
		ft_errormsg(SYNTAX_ERROR, NULL);
		free_list_dmh(data);
		free_list_token(data);
		free(data->input);
		set_exit_status(data, 1);
		return (1);
	}
	return (0);
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
	data->lexer.syntax_error = 0;
	data->lexer.rd_flag = 0;
	data->lexer.cmd_flag = 0;
	data->lexer.pipe_flag = 0;
	data->lexer.token = NULL;
	while (data->input[data->lexer.input_len])
		data->lexer.input_len++;
}

int	handle_spaces(t_data *data, int i)
{
	if (data->lexer.str_open == 1)
	{
		tokenize(data, T_WORD, data->lexer.tmp_str);
		data->lexer.str_open = 0;
	}
	while (data->input[i] == ' ' || data->input[i] == '\t')
		i++;
	return (i);
}

int	handle_under_score(t_data *data, int i, int j)
{
	int	new_i;

	data->lexer.exp_env = NULL;
	if (i == 2)
	{
		data->lexer.exp_tmp = ft_strdup_dmh(data, "_");
		return (1);
	}
	else
	{
		data->lexer.exp_tmp = ft_strndup_dmh(data, data->lexer.exp, j);
		new_i = ft_strlen(data->lexer.exp_tmp);
		data->lexer.exp_tmp = ft_strjoin_dmh(data, data->lexer.exp_tmp,
				ft_strdup_dmh(data, data->lexer.exp + (i - 1)));
		return (new_i);
	}
}

void	free_list_token(t_data *data)
{
	t_token	*tmp;

	while (data->lexer.token)
	{
		tmp = data->lexer.token->next;
		if (data->lexer.token != NULL)
		{
			free(data->lexer.token->str);
			free(data->lexer.token);
		}
		data->lexer.token = tmp;
	}
}
