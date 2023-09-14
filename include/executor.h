/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:41:04 by slampine          #+#    #+#             */
/*   Updated: 2023/09/14 11:15:24 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"
# include "utils.h"

int		executor(t_data *data, t_exec *exec);
int		is_builtin(char *cmd);
void	run_builtin(t_exec *exec, int spec, t_data *data);
void	find_n_exec(t_exec *exec, t_data *data);
int		is_abs_path(char *src);
char	*get_cmd_path(char *path_line, char *cmd);

#endif