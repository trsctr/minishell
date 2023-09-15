/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:20:07 by slampine          #+#    #+#             */
/*   Updated: 2023/09/15 12:37:26 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	fill_cmd(t_exec *exec, t_token *tok, int i)
{
	if (exec->cmd)
		free(exec->cmd);
	exec->cmd = ft_strdup(tok->str);
	if (exec->cmd == NULL)
		return (1);
	if (exec->argv[i])
		free(exec->argv[i]);
	exec->argv[i] = ft_strdup(tok->str);
	if (exec->argv[i] == NULL)
		return (1);
	return (0);
}

int	fill_word(t_exec *exec, t_token *tok, int i, int prev)
{
	if ((tok->type == T_WORD) && !(prev >= 46 && prev <= 49))
	{
		exec->argv[i] = ft_strdup(tok->str);
		if (exec->argv[i] == NULL)
			return (1);
	}
	else if (tok->type == T_EMPTY_WORD)
	{
		exec->argv[i] = ft_strdup("");
		if (exec->argv[i] == NULL)
			return (1);
	}
	return (0);
}

int	filler_util(t_exec *exec, t_token *tok)
{
	int		i;
	int		prev;

	i = 0;
	prev = 0;
	while (tok && tok->type != T_PIPE)
	{
		if (tok->type == T_CMD)
		{
			if (fill_cmd(exec, tok, 0))
				return (1);
		}
		else if (((tok->type == T_WORD) && !(prev >= 46 && prev <= 49))
			|| tok->type == T_EMPTY_WORD)
		{
			if (fill_word(exec, tok, i, prev))
				return (1);
		}
		else if (i == 0)
			(fill_cmd(exec, tok, i));
		i++;
		prev = tok->type;
		tok = tok->next;
	}
	return (0);
}

int	fill_exec_from_tokens(t_exec *exec)
{
	int		size;
	t_token	*tok;

	size = 1;
	tok = exec->token;
	while (tok)
	{
		if (tok->type == T_WORD || tok->type == T_EMPTY_WORD)
			size++;
		if (tok->type == T_PIPE)
			break ;
		tok = tok->next;
	}
	exec->argv = ft_calloc((1 + size), sizeof(char *));
	if (exec->argv == NULL)
		return (1);
	tok = exec->token;
	if (filler_util(exec, tok))
		return (1);
	return (0);
}
