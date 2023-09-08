/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:31:33 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/07 16:24:54 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# include <signal.h>
# include <stdarg.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "builtins.h"
# include "parser.h"
# include "lexer.h"


void	prompt(t_data *data);
char	*get_input(void);
void	heredoc_signals();
void	listen_signals(void);
void	handle_sig_int(int signal);
void	toggle_echoctl(void);
void	reset_signals(void);
int		is_builtin(char *input);
int		ft_printf_stderr(const char *format, ...);
#endif