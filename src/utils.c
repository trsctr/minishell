/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:46:07 by slampine          #+#    #+#             */
/*   Updated: 2023/09/05 16:47:22 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_envsize(t_ev *lst)
{
	int		i;
	t_ev	*curr;

	i = 0;
	curr = lst;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

/**
 * @brief function to clear and free exec list
 * 
 * @param exec 
 */
void free_exec(t_exec *exec)
{
	int		i;
	t_exec	*temp;

	while (exec)
	{
		temp = exec->next;
		i = 0;
		while (exec->argv[i])
		{
			free(exec->argv[i]);
			i++;
		}
		free(exec->argv);
		exec->next = NULL;
		exec = temp;
	}
}
