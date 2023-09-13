/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:53:01 by slampine          #+#    #+#             */
/*   Updated: 2023/09/13 18:45:15 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	create_heredoc(t_data *data, t_exec *exec, t_token *token)
{
	int		fd;
	char	*line;

	g_sig_status = 0;
	fd = open(exec->heredoc, O_CREAT | O_RDWR | O_TRUNC, 0777);
	line = readline("> ");
	while (line)
  //while (line && ft_strcmp(line, token->str))
	{
		if (((ft_strlen(line) == ft_strlen(token->str)) \
		&& !ft_memcmp(line, token->str, ft_strlen(line))) \
		|| g_sig_status)
			break ;
		if (line[0] == '$')
		{
			line = ft_getenv(data, line + 1);
			if (!line)
				line = ft_strdup("");
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
		line = readline("> ");
	}
	close(fd);
	if (g_sig_status == 1)
	{
	//	terminal_reset(data);
		return (1);
	}
	if (!line)
	{
		terminal_reset(data);
		redir_in(exec, exec->heredoc);
		return (0);
	}
	free(line);
	terminal_reset(data);
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
