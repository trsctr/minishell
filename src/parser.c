/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:48:54 by slampine          #+#    #+#             */
/*   Updated: 2023/09/08 15:44:48 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	create_pipes(t_exec *cmd)
{
	int		pipe_fd[OPEN_MAX][2];
	int		i;
	int		input;
	int		status;

	i = 0;
	input = 0;
	while (cmd)
	{
		if (cmd->next)
		{
			status = pipe(pipe_fd[i]);
			if (status == -1)
			{
				printf("Error with pipe\n");
				continue ;
			}
			cmd->read_fd = input;
			cmd->write_fd = pipe_fd[i][1];
			input = pipe_fd[i][0];
		}
		else
			cmd->read_fd = input;
		cmd = cmd->next;
		i++;
	}
}

int	redir_in(t_exec *cmd, t_token *token)
{
	int	fd;

	fd = open(token->str, O_RDONLY);
	if (fd == -1)
		return (1);
	if (cmd->read_fd > 2)
		close(cmd->read_fd);
	cmd->read_fd = fd;
	return (0);
}

int	redir_out_trunc(t_exec *cmd, t_token *token)
{
	int	fd;

	fd = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return (1);
	if (cmd->write_fd > 2)
		close(cmd->write_fd);
	cmd->write_fd = fd;
	return (0);
}

int	redir_out_app(t_exec *cmd, t_token *token)
{
	int	fd;

	fd = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		return (1);
	if (cmd->write_fd > 2)
		close(cmd->write_fd);
	cmd->write_fd = fd;
	return (0);
}

int	handle_rds(t_exec *cmd)
{
	t_token	*tok;

	tok = cmd->token;
	while (tok)
	{
		if (tok->type == T_RD_S_L)
		{
			if (redir_in(cmd, tok->next))
				return (1);
		}
		if (tok->type == T_RD_D_L)
		{
			if (redir_heredoc(cmd, tok->next))
				return (1);
		}
		if (tok->type == T_RD_S_R)
		{
			if (redir_out_trunc(cmd, tok->next))
				return (1);
		}
		if (tok->type == T_RD_D_R)
		{
			if (redir_out_app(cmd, tok->next))
				return (1);
		}
		tok = tok->next;
	}
	return (0);
}

void	create_execs(t_data *data)
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
	cmd = data->exec;
	while (cmd)
	{
		tok = cmd->token;
		while (tok)
		{
			if (tok->next)
			{
				if (tok->next->type == T_PIPE)
					tok->next = NULL;
			}
			tok = tok->next;
		}
		cmd = cmd->next;
	}
}

void	fill_exec_from_tokens(t_exec *exec)
{
	int		size;
	int		i;
	t_token	*tok;

	size = 1;
	tok = exec->token;
	while (tok)
	{
		if (tok->type == T_WORD)
			size++;
		tok = tok->next;
	}
	exec->argv = ft_calloc((1 + size), sizeof(char *));
	tok = exec->token;
	i = 0;
	while (tok)
	{
		if (tok->type == T_CMD)
		{
			exec->cmd = ft_strdup(tok->str);
			exec->argv[i] = ft_strdup(tok->str);
			i++;
		}
		if (tok->type == T_WORD)
		{
			exec->argv[i] = ft_strdup(tok->str);
			i++;
		}
		tok = tok->next;
	}
}

void	parser(t_data *data)
{
	t_exec	*cmd;

	create_execs(data);
	cmd = data->exec;
	create_pipes(cmd);
	while (cmd)
	{
		fill_exec_from_tokens(cmd);
		if (handle_rds(cmd))
			break ;
		cmd = cmd->next;
	}
}
