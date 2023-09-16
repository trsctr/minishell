/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expandables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:02:34 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/16 18:03:51 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_question_mark(t_data *data, int i)
{
	char	*tmp;

	if (data->lexer.exp[i] == '?')
	{
		tmp = ft_itoa(data->exit_status);
		if (i > 1)
		{
			data->lexer.exp_tmp = ft_strndup_dmh(data, data->lexer.exp, i - 1);
			data->lexer.exp_tmp = ft_strjoin_dmh(data, data->lexer.exp_tmp,
					tmp);
			data->lexer.exp_tmp = ft_strjoin_dmh(data, data->lexer.exp_tmp,
					data->lexer.exp + (i + 1));
		}
		else
		{
			data->lexer.exp_tmp = ft_strdup_dmh(data, tmp);
			data->lexer.exp_tmp = ft_strjoin_dmh(data, data->lexer.exp_tmp,
					data->lexer.exp + (i + 1));
		}
		data->lexer.exp = ft_strdup_dmh(data, data->lexer.exp_tmp);
		free(tmp);
		return (ft_strlen(data->lexer.exp));
	}
	return (i);
}

int	fill_exp_from_middle(t_data *data, int i, int j, int keylen)
{
	if (ft_getenv(data, data->lexer.exp_tmp) == NULL
		&& data->lexer.exp_tmp[0] == '_' && data->lexer.exp_tmp[1] == '\0')
		return (handle_under_score(data, i, j));
	if (ft_getenv(data, data->lexer.exp_tmp) == NULL)
		data->lexer.exp_env = NULL;
	else
		data->lexer.exp_env = ft_strdup_dmh(data,
				ft_getenv(data, data->lexer.exp_tmp));
	data->lexer.exp_tmp = ft_strndup_dmh(data, data->lexer.exp, j);
	if (data->lexer.exp_env != NULL)
	{
		data->lexer.exp_tmp = ft_strjoin_dmh(data,
				data->lexer.exp_tmp, data->lexer.exp_env);
		data->lexer.exp_tmp = ft_strjoin_dmh(data, data->lexer.exp_tmp,
				ft_strdup_dmh(data, data->lexer.exp + i));
	}
	else
	{
		data->lexer.exp_tmp = ft_strjoin_dmh(data, data->lexer.exp_tmp,
				ft_strdup_dmh(data, data->lexer.exp + i));
	}
	if (data->lexer.exp_env == NULL)
		return (keylen);
	return (ft_strlen(data->lexer.exp_env));
}

int	fill_exp_from_start(t_data *data, int i)
{
	int	new_i;

	if (ft_getenv(data, data->lexer.exp_tmp) == NULL
		&& data->lexer.exp_tmp[0] == '_' && data->lexer.exp_tmp[1] == '\0')
		return (handle_under_score(data, i, 0));
	if (ft_getenv(data, data->lexer.exp_tmp) == NULL)
		data->lexer.exp_env = NULL;
	else
		data->lexer.exp_env = ft_strdup_dmh(data,
				ft_getenv(data, data->lexer.exp_tmp));
	if (data->lexer.exp_env != NULL)
	{
		data->lexer.exp_tmp = ft_strdup_dmh(data, data->lexer.exp_env);
		new_i = ft_strlen(data->lexer.exp_tmp);
		data->lexer.exp_tmp = ft_strjoin_dmh(data, data->lexer.exp_tmp,
				ft_strdup_dmh(data, data->lexer.exp + i));
	}
	else
	{
		new_i = 0;
		data->lexer.exp_tmp = ft_strdup_dmh(data, data->lexer.exp + i);
	}
	return (new_i);
}

int	fill_expandable(t_data *data, int i)
{
	int	j;

	j = i;
	if (data->lexer.exp[i] >= '0' && data->lexer.exp[i] <= '9')
	{
		i++;
		data->lexer.exp_tmp = ft_strndup_dmh(data, data->lexer.exp + j, i - j);
	}
	else if ((data->lexer.exp[i] >= 'a' && data->lexer.exp[i] <= 'z')
		|| (data->lexer.exp[i] >= 'A' && data->lexer.exp[i] <= 'Z')
		|| (data->lexer.exp[i] >= '_'))
	{
		while ((data->lexer.exp[i] >= 'a' && data->lexer.exp[i] <= 'z')
			|| (data->lexer.exp[i] >= 'A' && data->lexer.exp[i] <= 'Z')
			|| (data->lexer.exp[i] >= '0' && data->lexer.exp[i] <= '9')
			|| (data->lexer.exp[i] >= '_'))
			i++;
		data->lexer.exp_tmp = ft_strndup_dmh(data, data->lexer.exp + j, i - j);
	}
	if (j > 1)
		return (fill_exp_from_middle(data, i, j - 1, 
				ft_strlen(data->lexer.exp_tmp)));
	else
		return (fill_exp_from_start(data, i));
}

void	check_expandable(t_data *data, int start, int len)
{
	int	i;

	i = 0;
	data->lexer.exp = ft_strndup_dmh(data, data->input + start, len);
	while (data->lexer.exp[i])
	{
		if (data->lexer.exp[i] == '$')
		{
			while (data->lexer.exp[i] == '$')
				i++;
			if (!(data->lexer.exp[i] >= 'a' && data->lexer.exp[i] <= 'z')
				&& !(data->lexer.exp[i] >= 'A' && data->lexer.exp[i] <= 'Z')
				&& !(data->lexer.exp[i] >= '0' && data->lexer.exp[i] <= '9')
				&& !(data->lexer.exp[i] >= '_'))
			{
				i = check_question_mark(data, i);
				continue ;
			}
			i = fill_expandable(data, i);
			data->lexer.exp = ft_strdup_dmh(data, data->lexer.exp_tmp);
		}
		else
			i++;
	}
}
