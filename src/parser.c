/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:48:54 by slampine          #+#    #+#             */
/*   Updated: 2023/09/15 20:58:52 by slampine         ###   ########.fr       */
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
		{
			free_list_token(data);
			ft_errormsg(MALLOC_FAIL, NULL);
			return (1);
		}
		if (handle_rds(data, cmd))
		{
			free_list_token(data);
			return (2);
		}
		if (ft_strcmp(cmd->cmd, "<<"))
			ft_change_var(&data->env_var, "_", cmd->cmd);
		cmd = cmd->next;
	}
	free_list_token(data);
	return (0);
}
