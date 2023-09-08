/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_executables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:00:15 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/08 22:16:57 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	check_token_pipes(t_data *data)
{
	data->lexer.pipe_flag = 1;
	if(data->lexer.rd_flag == 0 && data->lexer.cmd_flag == 0)
		data->lexer.syntax_error = 1;
	else
	{
		data->lexer.rd_flag = 0;
		data->lexer.cmd_flag = 0;
	}
}

t_token	*check_token_redirect(t_data *data, t_token *tmp)
{
	if(tmp->type == T_RD_S_L || tmp->type == T_RD_S_R
		|| tmp->type == T_RD_D_L || tmp->type == T_RD_D_R)
	{
		data->lexer.pipe_flag = 0;
		if(tmp->next && (tmp->next->type == T_WORD
			|| tmp->next->type == T_EMPTY_WORD))
		{
			tmp = tmp->next;
			data->lexer.rd_flag = 1;
		}
		else
			data->lexer.syntax_error = 1;
	}
	return(tmp);
}

void	check_token(t_data *data)
{
	t_token *tmp;

	tmp = data->lexer.token;
	while(tmp && data->lexer.syntax_error == 0)
	{
		if(tmp->type == T_PIPE)
			check_token_pipes(data);
		if(tmp->type == T_WORD || tmp->type == T_EMPTY_WORD)
		{
			data->lexer.pipe_flag = 0;
			if(data->lexer.cmd_flag == 0)
			{
				tmp->type = T_CMD;
				data->lexer.cmd_flag = 1;
			}
		}
		tmp = check_token_redirect(data, tmp);
		tmp = tmp->next;
	}
	if(data->lexer.pipe_flag)
		data->lexer.syntax_error = 1;
}

// nama pitaa toimia

// > file1 | echo jee

// > file1 | > file2

// > file1 | > file2 | > file3

// > file1 | echo jee | > file2