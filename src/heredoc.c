/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:53:01 by slampine          #+#    #+#             */
/*   Updated: 2023/09/07 12:52:53 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	create_heredoc(t_exec *exec)
{
	int		fd;
	char	*line;

	fd = open(exec->infile, O_CREAT| O_RDWR| O_TRUNC, 0777);
	heredoc_signals();
	line = readline(">");
	while (line && ft_strcmp(line, exec->delim))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
		line = readline(">");
	}
	reset_signals();
	free(line);
	close (fd);
	return (0);
}

void	name_heredoc(t_exec *exec)
{
	static int	i = 0;
	char		*num;

	num = ft_itoa(i);
	exec->infile = ft_strjoin("temp_heredoc_file_", num);
	free(num);
	i++;
}

int handle_heredocs(t_exec *exec)
{
	while (exec)
	{
		if (exec->redir_in == 2)
		{
			name_heredoc(exec);
			create_heredoc(exec);
		}
		exec = exec->next;
	}
	return (0);
}

