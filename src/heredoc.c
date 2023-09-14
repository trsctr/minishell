/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:53:01 by slampine          #+#    #+#             */
/*   Updated: 2023/09/14 17:32:20 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/**
 * @brief helper function to expand environment variables when called in heredoc
 * 
 * @param data 
 * @param line 
 * @return char* 
 */
char	*expand_var_hd(t_data *data, char *line)
{
	char	*temp;

	temp = ft_getenv(data, line + 1);
	free(line);
	if (!temp)
		return (ft_strdup(""));
	else
		return (ft_strdup(temp));
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
		if (line[0] == '$')
			line = expand_var_hd(data, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
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
