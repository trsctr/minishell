/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:06:16 by slampine          #+#    #+#             */
/*   Updated: 2023/09/07 16:39:33 by slampine         ###   ########.fr       */
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

void	parser(t_data *data);
# endif