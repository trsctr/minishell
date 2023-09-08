/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:53:01 by slampine          #+#    #+#             */
/*   Updated: 2023/09/08 15:34:15 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	create_heredoc(t_exec *exec, t_token *token)
{
	int		fd;
	char	*line;

	fd = open(exec->heredoc, O_CREAT| O_RDWR| O_TRUNC, 0777);
	heredoc_signals();
	line = readline(">");
	while (line && ft_strcmp(line, token->str))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
		line = readline(">");
	}
	if (!line)
	{
		printf("EOF received\n");
		close (fd);
		return (1);
	}
	reset_signals();
	free(line);
	close (fd);
	return (0);
}

int	name_heredoc(t_exec *exec)
{
	static int	i = 0;
	char		*num;

	num = ft_itoa(i);
	exec->heredoc = ft_strjoin("temp_heredoc_file_", num);
	if (!exec->heredoc)
		return (1);
	free(num);
	i++;
	return (0);
}

int	redir_heredoc(t_exec *exec, t_token *token)
{
	if (name_heredoc(exec))
		return (1);
	if (create_heredoc(exec, token))
		return (1);
	exec->has_heredoc = 1;
	return (0);
}

