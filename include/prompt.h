/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:31:33 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/06 19:01:57 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# include <stdarg.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "builtins.h"


void	prompt(t_data *data);
char	*get_input(void);
void	listen_signals(void);
void	handle_sig_int(int signal);
void	toggle_echoctl(void);
void	reset_signals(void);
int		is_builtin(char *input);
int		ft_printf_stderr(const char *format, ...);
void	ft_errormsg(int errorcode, char *cmd);
void	terminal_reset(t_data *data);
void	terminal_setup(t_data *data);
int	only_spaces(char *line);
#endif