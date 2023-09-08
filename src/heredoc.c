/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:53:01 by slampine          #+#    #+#             */
/*   Updated: 2023/09/08 16:03:05 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	create_heredoc(t_data *data, t_exec *exec)
{
	int		fd;
	char	*line;

	g_sig_status = 0;
	fd = open(exec->infile, O_CREAT| O_RDWR| O_TRUNC, 0777);
	line = readline(">");
	while (line && ft_strcmp(line, exec->delim))
	{
		if (g_sig_status == 1)
			break ;
		if (line[0] == '$')
			line = expand_ev(data, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
		line = NULL;
		line = readline(">");
	}
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

int handle_heredocs(t_data *data)
{
	t_exec *exec;

	exec = data->exec;
	while (exec)
	{
		if (exec->redir_in == 2)
		{
			name_heredoc(exec);
			create_heredoc(data, exec);
		}
		exec = exec->next;
	}
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
