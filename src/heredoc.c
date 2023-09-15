/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:53:01 by slampine          #+#    #+#             */
/*   Updated: 2023/09/15 20:52:22 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/**
 * @brief this function writes out the line one character at a time
 * if there is an environment variable in the beginning, it is expanded
 * if they key is valid, and the loop jumps over it while printing the
 * line
 * 
 * @param data 
 * @param line 
 * @param fd 
 */
void	heredoc_handle_line(t_data *data, char *line, int fd)
{
	int	i;

	if (line[0] == '$')
		i = expand_var_in_heredoc(data, line, fd);
	else
		i = 0;
	while (line[i])
	{
		ft_putchar_fd(line[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
	free (line);
}

/**
 * @brief heredoc loop is executed in the main heredoc_create function
 * exits the loop if user inputs the delimiter, presses ctrl+c or ctrl+d
 * 
 * @param data main data struct
 * @param delim delimiter given by user on command line
 * @param fd file descriptor for the heredoc document
 * @return int 
 */
int	heredoc_loop(t_data *data, char *delim, int fd)
{
	char	*line;

	line = readline("> ");
	while (line)
	{
		if (((ft_strlen(line) == ft_strlen(delim)) \
		&& !ft_memcmp(line, delim, ft_strlen(line))))
		{
			free(line);
			return (0);
		}
		if (g_sig_status)
		{
			free(line);
			return (1);
		}
		heredoc_handle_line(data, line, fd);
		line = readline("> ");
	}
	return (0);
}

int	create_heredoc(t_data *data, t_exec *exec, t_token *token)
{
	int		fd;
	int		hd_status;

	g_sig_status = 0;
	fd = open(exec->heredoc, O_CREAT | O_RDWR | O_TRUNC, 0777);
	hd_status = heredoc_loop(data, token->str, fd);
	close(fd);
	if (hd_status)
		return (1);
	redir_in(exec, exec->heredoc);
	return (0);
}

int	name_heredoc(t_exec *exec)
{
	static int	i = 0;
	char		*num;
	char		*id;

	num = ft_itoa(i);
	id = ft_itoa(getpid());
	if (exec->heredoc)
	{
		unlink(exec->heredoc);
		free(exec->heredoc);
	}
	exec->heredoc = ft_strjoin(id, num);
	if (!exec->heredoc)
		return (1);
	free(num);
	free(id);
	i++;
	return (0);
}

int	redir_heredoc(t_data *data, t_exec *exec, t_token *token)
{
	if (name_heredoc(exec))
		return (1);
	exec->has_heredoc = 1;
	if (create_heredoc(data, exec, token))
		return (1);
	return (0);
}
