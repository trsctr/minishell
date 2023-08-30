/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:55:03 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/25 14:29:00 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "env_var.h"

/**
 * @brief saves environment variables to a linked list inside the ms struct
 * 
 * @param env 
 * @param ms 
 */
void	save_env_var(char **env, t_data *data)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	if (!env[i])
	{
		no_env_vars(data);
		return ;
	}
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			key = get_ev_key(env[i]);
			value = get_ev_value(env[i]);
			if (!ft_strcmp(key, "SHLVL"))
				value = update_shlvl(value);
			ft_new_env_var(&data->env_var, ft_new_evnode(key, value));
			free(key);
			free(value);
		}
		i++;
	}
}

/**
 * @brief retrieves the key of an environment variable from a string
 * in format key=value
 * 
 * @param str 
 * @return char* 
 */
char	*get_ev_key(char *str)
{
	int		len;
	char	*key;

	len = 0;
	while (str[len] != '=' && str[len] != '\0')
		len++;
	if (str[len] == '\0')
		return (NULL);
	len++;
	key = malloc(sizeof(char) * len);
	ft_strlcpy(key, str, len);
	return (key);
}

/**
 * @brief retrieves the value of an environment variable from a string
 * in format key=value
 * 
 * @param str 
 * @return char* 
 */
char	*get_ev_value(char *str)
{
	if (!ft_strchr(str, '='))
		return (NULL);
	else
		return (ft_strdup(ft_strchr(str, '=') + 1));
}

/**
 * @brief adds 1 to the value of SHLVL (shell level) environment variable
 * 
 * @param value 
 * @return char* 
 */
char	*update_shlvl(char *value)
{
	int	lvl;

	lvl = ft_atoi(value);
	lvl++;
	free(value);
	return (ft_itoa(lvl));
}

/**
 * @brief is called if no env vars are provided (like running env -i ./minishell)
 * 
 * @param ms 
 */
void	no_env_vars(t_data *data)
{
	char	pwd[200];

	getcwd(pwd, 200);
	ft_new_env_var(&data->env_var, ft_new_evnode("PWD", pwd));
	ft_new_env_var(&data->env_var, ft_new_evnode("SHLVL", "1"));
}

char	*get_var_key(char *str)
{
	int		len;
	char	*key;

	len = 0;
	while (str[len] != '=')
		len++;
	len++;
	key = malloc(sizeof(char) * len);
	ft_strlcpy(key, str, len);
	return (key);
}
