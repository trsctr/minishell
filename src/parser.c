/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:48:54 by slampine          #+#    #+#             */
/*   Updated: 2023/09/16 17:16:50 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"

void	give_tokens(t_data *data)
{
	t_exec	*cmd;
	t_exec	*temp;
	t_token	*tok;

	cmd = init_exec();
	data->exec = cmd;
	tok = data->lexer.token;
	cmd->token = tok;
	while (tok)
	{
		if (tok->type == T_PIPE)
		{
			temp = init_exec();
			cmd->next = temp;
			cmd = cmd->next;
			temp->token = tok->next;
		}
		tok = tok->next;
	}
}

void	create_execs(t_data *data)
{
	t_exec	*cmd;
	t_token	*tok;

	give_tokens(data);
	cmd = data->exec;
	while (cmd)
	{
		tok = cmd->token;
		while (tok)
		{
			if (tok->next)
			{
				if (tok->next->type == T_PIPE)
				{
					data->pipe_count++;
					break ;
				}
			}
			tok = tok->next;
		}
		cmd = cmd->next;
	}
}

int	parser(t_data *data)
{
	t_exec	*cmd;

	create_execs(data);
	cmd = data->exec;
	create_pipes(data, cmd);
	while (cmd)
	{
		if (fill_exec_from_tokens(cmd))
			malloc_error(data);
		if (handle_rds(data, cmd))
		{
			close_pipes(data);
			free(data->pipes);
			free_list_token(data);
			return (2);
		}
		if (cmd->cmd && ft_strcmp(cmd->cmd, "true"))
			ft_change_var(&data->env_var, "_", cmd->cmd);
		else
			ft_change_var(&data->env_var, "_", " ");
		cmd = cmd->next;
	}
	free_list_token(data);
	return (0);
}
