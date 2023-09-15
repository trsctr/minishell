/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:58:54 by slampine          #+#    #+#             */
/*   Updated: 2023/09/15 21:04:06 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	create_pipes(t_data *data, t_exec *cmd)
{
	int		i;
	int		status;
	
	i = 0;
	data->pipes = malloc(sizeof(int) * (2 * data->pipe_count));
	while (i != data->pipe_count)
	{
		status = pipe(data->pipes + (i * 2));
		if (status == -1)
		{
			ft_errormsg(PIPE_FAIL, NULL);
			break ;
		}
		i++;
	}
	set_pipes(data, cmd);
}
	
void set_pipes(t_data *data, t_exec *cmd)
{
	int	i;
	int	input;

	
	i = 0;
	input = 0;
	while (cmd)
	{
		if (cmd->next)
		{
			cmd->read_fd = input;
			cmd->write_fd = data->pipes[i + 1];
			input = data->pipes[i];
			i += 2;
		}
		else
			cmd->read_fd = input;
		cmd = cmd->next;
	}
}

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->pipe_count * 2))
	{
		close(data->pipes[i]);
		i++;
	}
}