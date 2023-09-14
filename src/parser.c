/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:48:54 by slampine          #+#    #+#             */
/*   Updated: 2023/09/14 11:21:13 by slampine         ###   ########.fr       */
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
				ft_errormsg(PIPE_FAIL, NULL);
				break ;
			}
			cmd->read_fd = input;
			cmd->write_fd = pipe_fd[i][1];
			input = pipe_fd[i++][0];
		}
		else
			cmd->read_fd = input;
		cmd = cmd->next;
	}
}

int	redir_in(t_exec *cmd, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_errormsg(FILE_NOT_FOUND, file);
	if (cmd->read_fd > 2)
		close(cmd->read_fd);
	cmd->read_fd = fd;
	return (0);
}

int	redir_out_trunc(t_exec *cmd, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return (1);
	if (cmd->write_fd > 2)
		close(cmd->write_fd);
	cmd->write_fd = fd;
	return (0);
}

int	redir_out_app(t_exec *cmd, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		return (1);
	if (cmd->write_fd > 2)
		close(cmd->write_fd);
	cmd->write_fd = fd;
	return (0);
}

int	handle_out(t_exec *cmd, t_token *tok)
{
	if (tok->type == T_RD_S_R)
	{
		if (redir_out_trunc(cmd, tok->next->str))
			return (1);
	}
	if (tok->type == T_RD_D_R)
	{
		if (redir_out_app(cmd, tok->next->str))
			return (1);
	}
	return (0);
}

int	handle_rds(t_data *data, t_exec *cmd)
{
	t_token	*tok;

	tok = cmd->token;
	while (tok && tok->type != T_PIPE)
	{
		if (tok->type == T_RD_S_L)
		{
			if (redir_in(cmd, tok->next->str))
				return (1);
		}
		if (tok->type == T_RD_D_L)
		{
			if (redir_heredoc(data, cmd, tok->next))
				return (1);
		}
		if (tok->type == T_RD_D_R || tok->type == T_RD_S_R)
		{
			if (handle_out(cmd, tok))
				return (1);
		}
		tok = tok->next;
	}
	return (0);
}

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
					break ;
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
	create_pipes(cmd);
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
			return (1);
		}
		ft_change_var(&data->env_var, "_", cmd->cmd);
		cmd = cmd->next;
	}
	free_list_token(data);
	return (0);
}
