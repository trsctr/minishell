/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:37:30 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/14 14:26:51 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_var.h"
#include "builtins.h"

/**
 * @brief helper function for printing out the environment variables
 * if export is run without arguments
 * 
 * @param vars 
 * @param fd 
 */
static void	export_print_vars(t_ev **vars, int fd)
{
	t_ev	*curr;

	curr = *vars;
	while (curr)
	{
		ft_dprintf(fd, "declare -x %s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

/**
 * @brief export loop is called in the main export function
 * this handles multiple arguments in the while loop one at the time
 * 
 * @param data 
 * @param exec 
 */
static void	export_loop(t_data *data, t_exec *exec)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (exec->argv[i])
	{
		if (!ft_strchr(exec->argv[i], '='))
			continue ;
		key = get_ev_key(exec->argv[i]);
		if (!key_is_valid(key))
		{
			ft_errormsg(EXPORT_NOT_VALID, exec->argv[i]);
			free(key);
			set_exit_status(data, 1);
			i++;
			continue ;
		}
		value = get_ev_value(exec->argv[i]);
		ft_change_var(&data->env_var, key, value);
		free(key);
		free(value);
		i++;
	}
}

/**
 * @brief builtin export command, saves new environment variables
 * as long as the key is valid. if no arguments are presented, list of
 * environment variables are printed with the help of export_print_vars function
 * if arguments are presented, they are handled in export_loop function.
 * 
 * @param data 
 * @param exec 
 */
void	builtin_export(t_data *data, t_exec *exec)
{
	set_exit_status(data, 0);
	if (!exec->argv[1])
		export_print_vars(&data->env_var, exec->write_fd);
	else
		export_loop(data, exec);
}
