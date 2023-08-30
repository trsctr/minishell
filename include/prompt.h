/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:31:33 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/25 14:12:06 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# include <signal.h>
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

#endif