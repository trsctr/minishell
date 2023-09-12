/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:46:22 by slampine          #+#    #+#             */
/*   Updated: 2023/09/12 20:17:14 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

void	free_array(char **array);
int		ft_envsize(t_ev *lst);
void	free_exec(t_exec *exec);
char	*ft_getenv(t_data *data, char *key);

#endif