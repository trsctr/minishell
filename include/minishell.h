/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:58:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/16 15:34:37 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/include/libft.h"
#include <stdlib.h>

typedef struct s_msg {
	char	*prompt;
	char	*cmd_not_found;
	char	*dir_bad;
} t_msg;

typedef struct s_ms {
	t_msg	*msg;
	t_list	*env_var;
} t_ms;

char	*get_input(void);
void	prompt(void);