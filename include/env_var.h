/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:06:39 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/21 13:09:38 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_ev *ft_new_evnode(char *key, char *value);
void	ft_new_env_var(t_ev **vars, t_ev *new_var);
char *get_var_key(char *str);
t_ev	*ft_find_var(t_ev **vars, char *key);
void	ft_delete_var(t_ev **vars, char *key);