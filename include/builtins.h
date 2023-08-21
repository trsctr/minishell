/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:20:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/21 15:43:29 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void builtin_env(t_ms *ms);
void	builtin_pwd(void);
void builtin_cd(char *dir, t_ms *ms);
void builtin_export (t_ms *ms, char *arg);
void builtin_unset (t_ms *ms, char *key);

