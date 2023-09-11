/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:53:01 by slampine          #+#    #+#             */
/*   Updated: 2023/09/11 16:06:46 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

char	*expand_ev(t_data *data, char *line);

int	create_heredoc(t_data *data, t_exec *exec, t_token *token)
{
	int		fd;
	char	*line;

	g_sig_status = 0;
	fd = open(exec->heredoc, O_CREAT| O_RDWR| O_TRUNC, 0777);
	line = readline(">");
	while (line && ft_strcmp(line, token->str))
	{
		if (g_sig_status == 1)
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
		line = readline(">");
	}
	if (!line)
	{
		printf("EOF received\n");
		close (fd);
		unlink(exec->heredoc);
		free(exec->heredoc);
		return (1);
	}
	free(line);
	close (fd);
	unlink(exec->heredoc);
	free(exec->heredoc);
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
	if (create_heredoc(data, exec, token))
		return (1);
	exec->has_heredoc = 1;
	return (0);
}

char	*expand_ev(t_data *data, char *line)
{
	t_ev	*temp;

	temp = ft_find_var(&data->env_var, line + 1);
	if (!temp)
		return (ft_strdup(""));
	else
		return (ft_strdup(temp->value));
}
