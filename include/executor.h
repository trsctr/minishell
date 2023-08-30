/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:41:04 by slampine          #+#    #+#             */
/*   Updated: 2023/08/30 14:07:26 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"
# include "utils.h"

int		executor(t_data *data, t_exec *exec);
int		old_executor(char *source, t_data *data);
void	run_builtin(t_exec *exec, int spec, t_data *data);
void	find_n_exec(t_exec *exec, t_data *data);

#endif