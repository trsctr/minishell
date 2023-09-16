/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:48:39 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/15 14:52:06 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief helper function to expand environment variables when called in 
 * heredoc and prints out the value if the key is valid
 * returns the length of the $KEYWORD to heredoc handle line function which 
 * writes out the line one character at the time
 * @param data 
 * @param line 
 * @return char* 
 */
int	expand_var_in_heredoc(t_data *data, char *line, int fd)
{
	char	*var;
	char	*key;
	int		i;

	i = 1;
	if (line[i] >= '0' && line[i] <= '9')
		return (2);
	else if ((line[i] >= 'a' && line[i] <= 'z')
		|| (line[i] >= 'A' && line[i] <= 'Z')
		|| (line[i] >= '_'))
	{
		while ((line[i] >= 'a' && line[i] <= 'z') 
			|| (line[i] >= 'A' && line[i] <= 'Z')
			|| (line[i] >= '0' && line[i] <= '9') || (line[i] >= '_'))
			i++;
		key = ft_substr(line, 1, i -1);
		var = ft_getenv(data, key);
		if (!var)
			ft_putstr_fd("", fd);
		else
			ft_putstr_fd(var, fd);
		free(key);
		return (i);
	}
	return (0);
}
