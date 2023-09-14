/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:06:16 by slampine          #+#    #+#             */
/*   Updated: 2023/09/14 16:09:22 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "heredoc.h"

# define T_CMD          42
# define T_WORD         43
# define T_EMPTY_WORD   44
# define T_PIPE         45
# define T_RD_S_L       46
# define T_RD_S_R       47
# define T_RD_D_L       48
# define T_RD_D_R       49

int	parser(t_data *data);
int	redir_in(t_exec *cmd, char *file);
int	fill_cmd(t_exec *exec, t_token *tok, int i);
int	fill_word(t_exec *exec, t_token *tok, int i, int prev);
int	filler_util(t_exec *exec);
int	fill_exec_from_tokens(t_exec *exec);
int	handle_rds(t_data *data, t_exec *cmd);
# endif