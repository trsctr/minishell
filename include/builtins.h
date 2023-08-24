/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:20:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/22 20:20:43 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_cmd {
	char	*cmd;
	char	**arg;
	int		argcount;
} t_cmd;

void	builtin_env(t_ms *ms);
void	builtin_pwd(t_cmd *cmd);
void	builtin_cd(t_ms *ms, t_cmd *cmd);
void	builtin_export(t_ms *ms, t_cmd *cmd);
void	builtin_unset(t_ms *ms, t_cmd *cmd);
void	builtin_echo(t_ms *ms, t_cmd *cmd);

#endif