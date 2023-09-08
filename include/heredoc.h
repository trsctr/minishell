/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:53:19 by slampine          #+#    #+#             */
/*   Updated: 2023/09/08 16:30:00 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "minishell.h"
# include "prompt.h"
# include "env_var.h"

int	create_heredoc(t_data *data, t_exec *exec, t_token *token);
int	name_heredoc(t_exec *exec);
int handle_heredocs(t_data *data);
int	redir_heredoc(t_data *data, t_exec *exec, t_token *token);


#endif