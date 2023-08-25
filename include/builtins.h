/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:20:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/25 14:43:04 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_cmd {
	char	*cmd;
	char	**arg;
	int		argcount;
} t_cmd;

void	builtin_env(t_data *data);
void	builtin_pwd(void);
void	builtin_cd(t_data *data, t_exec *exec);
void	builtin_export(t_data *data, t_exec *exec);
void	builtin_unset(t_data *data, t_exec *exec);
void	builtin_echo(t_data *data, t_exec *exec);

#endif