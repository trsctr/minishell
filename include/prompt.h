/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:31:33 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/11 17:40:55 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# include <stdarg.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "builtins.h"
# include "parser.h"
# include "lexer.h"


void	prompt(t_data *data);
char	*get_input(void);
void	handle_sig_int(int signal, siginfo_t *info, void *context);
int		is_builtin(char *input);
int		ft_printf_stderr(const char *format, ...);
void	ft_errormsg(int errorcode, char *cmd);
void	terminal_reset(t_data *data);
void	terminal_setup(t_data *data);
int		only_spaces(char *line);
#endif