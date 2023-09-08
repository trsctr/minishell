/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:49:06 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/08 20:55:28 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void malloc_error(t_data *data)
{
	ft_errormsg(MALLOC_FAIL, NULL);
	clear_data(data);
	exit(1);
}

void clear_data(t_data *data)
{
	ft_clear_evlist(data);

}