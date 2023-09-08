/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:53:19 by slampine          #+#    #+#             */
/*   Updated: 2023/09/08 15:47:20 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "minishell.h"
# include "prompt.h"
# include "env_var.h"

int	create_heredoc(t_data *data, t_exec *exec);
void	name_heredoc(t_exec *exec);
int handle_heredocs(t_data *data);
#endif