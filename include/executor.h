/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:41:04 by slampine          #+#    #+#             */
/*   Updated: 2023/08/28 10:22:21 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"
# include "utils.h"

int		executor(t_data *data, t_exec *exec);
int		old_executor(char *source, t_data *data);
void	run_builtin(t_exec *exec, int spec, t_data *data);

#endif