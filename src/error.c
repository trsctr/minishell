/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:09:50 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/18 17:16:33 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	malloc_error(t_data *data)
{
	ft_errormsg(MALLOC_FAIL, NULL);
	reset_signals();
	terminal_reset(data);
	if (data->lexer.dmh_list != NULL)
		free_list_dmh(data);
	if (data->lexer.token != NULL)
		free_list_token(data);
	clear_data(data);
	exit(1);
}

/**
 * @brief prints an error message based on given error code
 * 
 * @param errorcode 
 * @param cmd required if printing an error containing the command
 * or argument
 */
void	ft_errormsg(int errorcode, char *cmd)
{
	if (errorcode == BAD_CMD)
		ft_dprintf(2, "minishell: Command not found: %s\n", cmd);
	else if (errorcode == MALLOC_FAIL)
		ft_dprintf(2, "minishell: Memory allocation failed\n");
	else if (errorcode == PIPE_FAIL)
		ft_dprintf(2, "minishell: Piping failed\n");
	else if (errorcode == FORK_FAIL)
		ft_dprintf(2, "minishell: Fork error\n");
	else if (errorcode == SYNTAX_ERROR)
		ft_dprintf(2, "minishell: Syntax error\n");
	else if (errorcode == EXPORT_NOT_VALID)
		ft_dprintf(2, "minishell: export: '%s' not a valid identifier\n", cmd);
	else if (errorcode == EXIT_BAD_VALUE)
		ft_dprintf(2, "minishell: exit: %s: numeric argument needed\n", cmd);
	else if (errorcode == FILE_NOT_FOUND)
		ft_dprintf(2, "minishell: %s no such file or directory\n", cmd);
	else if (errorcode == CMD_IS_DIR)
		ft_dprintf(2, "minishell: %s is a directory\n", cmd);
	else if (errorcode == EXEC_FAIL)
		ft_dprintf(2, "minishell: %s: execution error\n", cmd);
	else if (errorcode == PERMISSION_DENIED)
		ft_dprintf(2, "minishell: %s: permission denied\n", cmd);
}
