/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:53:19 by slampine          #+#    #+#             */
/*   Updated: 2023/09/06 14:32:17 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "minishell.h"

int	create_heredoc(t_exec *exec);
void	name_heredoc(t_exec *exec);
int handle_heredocs(t_exec *exec);
#endif