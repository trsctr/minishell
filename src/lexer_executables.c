/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_executables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:00:15 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/06 23:27:03 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_executable_solver(char *word, char *part, int i, int j)
{
	char *res;

	res = malloc(sizeof(char) * (ft_strlen(word) + ft_strlen(part) + 2));
	if(res == NULL)
		exit_error(NULL, "malloc error\n");						// kayta oikeaa exit error
	while(part[++i])
		res[i] = part[i];
	res[i] = '/';
	i++;
	while(word[j])
	{
		res[i] = word[j];
		i++;
		j++;
	}
	res[i] = '\0';
	if(access(res, X_OK) == 0)
	{
		free(res);
		return(1);
	}
	free(res);
	return(0);
}

int	check_executable(t_data *data, char *word)
{
	char	*path;												// liian pitka funktio
	int	start;
	int	result;
	int	i;

	result = 0;
	i = 0;
	if(!ft_strcmp(word, "echo") || !ft_strcmp(word, "cd")
	|| !ft_strcmp(word, "pwd") || !ft_strcmp(word, "export")
	|| !ft_strcmp(word, "unset") || !ft_strcmp(word, "env")
	|| !ft_strcmp(word, "exit"))
		return (1);
	path = getenv("PATH");										// korvaa omalla vastaavalla jos tarvii
	if(path == NULL)
		exit_error(NULL, "failed to get path\n");				// kayta oikeaa exit error
	while(path[i])
	{
		start = i;
		while(path[i] != ':' && path[i] != '\0')
			i++;
		result += check_executable_solver(word, ft_strndup_dmh(data,
			path + start, i - start), -1, 0);
        if(path[i] == ':')
            i++;
	}
	return(result);
}
