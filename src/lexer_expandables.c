/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expandables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:02:34 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/07 15:46:06 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	fill_exp_from_middle(t_data *data, int i, int j)
{
	int new_i;

	data->lexer.exp_tmp = ft_strndup_dmh(data, data->lexer.exp, j);
		if(data->lexer.exp_env != NULL)
		{
			data->lexer.exp_tmp = ft_strjoin_dmh(data, data->lexer.exp_tmp,
				data->lexer.exp_env);
			new_i = ft_strlen(data->lexer.exp_tmp);
			data->lexer.exp_tmp = ft_strjoin_dmh(data, data->lexer.exp_tmp,
				ft_strdup_dmh(data, data->lexer.exp + i));
		}
		else
		{
			new_i = ft_strlen(data->lexer.exp_tmp);
			data->lexer.exp_tmp = ft_strjoin_dmh(data, data->lexer.exp_tmp,
				ft_strdup_dmh(data, data->lexer.exp + i));
		}
	return (new_i);
}

int	fill_exp_from_start(t_data *data, int i)
{
	int new_i;

	if(data->lexer.exp_env != NULL)
		{
			data->lexer.exp_tmp = ft_strdup_dmh(data, data->lexer.exp_env);
			new_i = ft_strlen(data->lexer.exp_tmp);
			data->lexer.exp_tmp = ft_strjoin_dmh(data, data->lexer.exp_tmp,
				ft_strdup_dmh(data, data->lexer.exp + i));
		}
		else
		{
			new_i = i;
			data->lexer.exp_tmp = ft_strdup_dmh(data, data->lexer.exp);
		}
	return (new_i);
}

int	fill_expandable(t_data *data, int i)
{
	int j;

	j = i;
	if((data->lexer.exp[i] >= 'a' && data->lexer.exp[i] <= 'z')
		|| (data->lexer.exp[i] >= 'A' && data->lexer.exp[i] <= 'Z')
		|| (data->lexer.exp[i] >= '_'))
		{
			while((data->lexer.exp[i] >= 'a' && data->lexer.exp[i] <= 'z')
				|| (data->lexer.exp[i] >= 'A' && data->lexer.exp[i] <= 'Z')
				|| (data->lexer.exp[i] >= '0' && data->lexer.exp[i] <= '9')
				|| (data->lexer.exp[i] >= '_'))
				i++;
			data->lexer.exp_tmp = ft_strndup_dmh(data,
				data->lexer.exp + j, i - j);
			if(getenv(data->lexer.exp_tmp) == NULL)						// korvaa omalla vastaavalla jos tarvii
				data->lexer.exp_env = NULL;
			else
				data->lexer.exp_env = ft_strdup_dmh(data,
					getenv(data->lexer.exp_tmp));						// korvaa omalla vastaavalla jos tarvii
		}
	j -= 1;
	if(j > 0)
		return(fill_exp_from_middle(data, i, j));
	else
		return(fill_exp_from_start(data, i));
}

void	check_expandable(t_data *data, int start, int len)
{
	int i;

	i = 0;
	data->lexer.exp = ft_strndup_dmh(data, data->input + start, len);
	while(data->lexer.exp[i])
	{
		if(data->lexer.exp[i] == '$')
		{
			//while(data->lexer.exp[i] == '$')
				i++;
			if(data->lexer.exp[i] == ' ' || data->lexer.exp[i] == '\t'
				|| data->lexer.exp[i] == '\0')
				continue;
			i = fill_expandable(data, i);
			data->lexer.exp = ft_strdup_dmh(data, data->lexer.exp_tmp);
			printf("%s\n", data->lexer.exp);
		}
		else
			i++;
	}
}

// $	->	$
// $$$	->	$$$
// $!	->	$!
// $e1	->	(tyhja)
// $1e	->	e