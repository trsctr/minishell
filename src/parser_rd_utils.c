/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:55:40 by slampine          #+#    #+#             */
/*   Updated: 2023/09/14 12:57:36 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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