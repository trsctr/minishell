/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:20:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/19 19:00:44 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void builtin_env(t_ms *ms);
void	builtin_pwd(void);
void builtin_cd(char *dir, t_ms *ms);