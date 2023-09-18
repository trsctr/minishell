/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:58:54 by slampine          #+#    #+#             */
/*   Updated: 2023/09/18 17:15:33 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"

int	create_pipes(t_data *data, t_exec *cmd)
{
	int		i;
	int		j;
	int		status;

	i = 0;
	j = 0;
	data->pipes = malloc(sizeof(int) * (2 * data->pipe_count));
	while (i != data->pipe_count)
	{
		status = pipe(data->pipes + (i * 2));
		if (status == -1)
		{
			handle_pipe_failure(data, i);
			ft_errormsg(PIPE_FAIL, NULL);
			return (1);
		}
		i++;
	}
	set_pipes(data, cmd);
	return (0);
}

void	set_pipes(t_data *data, t_exec *cmd)
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

void	handle_pipe_failure(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < i * 2)
	{
		close(data->pipes[j]);
		j++;
	}
	free(data->pipes);
	free_list_token(data);
}
