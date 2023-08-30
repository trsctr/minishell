/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:06:39 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/25 14:12:04 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

char	*get_ev_key(char *str);
char	*get_ev_value(char *str);
char	*get_var_key(char *str);
char	*update_shlvl(char *value);
void	no_env_vars(t_data *data);

t_ev	*ft_new_evnode(char *key, char *value);
void	ft_new_env_var(t_ev **vars, t_ev *new_var);
t_ev	*ft_find_var(t_ev **vars, char *key);
void	ft_delete_var(t_ev **vars, char *key);
void	ft_change_var(t_ev **vars, char *key, char *value);
void	ft_clear_evlist(t_data *data);

#endif