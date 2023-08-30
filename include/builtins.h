/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:20:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/30 13:57:49 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	builtin_env(t_data *data);
void	builtin_pwd(void);
void	builtin_cd(t_data *data, t_exec *exec);
void	builtin_export(t_data *data, t_exec *exec);
void	builtin_unset(t_data *data, t_exec *exec);
void	builtin_echo(t_exec *exec);

#endif