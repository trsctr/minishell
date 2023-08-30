/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:58:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/28 10:11:12 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/include/libft.h"
# include <stdlib.h>
# include <termios.h>
# include <fcntl.h>

# define BYELLOW "\001\e[0;33m\002"
# define RESET   "\001\e[0m\002"

# define PROMPT  "minishell> "
# define CMD_NOT_FOUND "Command not found"

typedef struct s_ev {
	char		*key;
	char		*value;
	struct s_ev	*next;
}	t_ev;

typedef struct s_exec{
	char			*cmd;
	char			**argv;
	int				read_fd;
	int				write_fd;
	struct s_exec	*next;
}				t_exec;


typedef struct s_data {
	t_ev	*env_var;
	t_exec	*exec;
}	t_data;

void	rl_replace_line(const char *text, int clear_undo);

t_data	*init_data(void);
void	save_env_var(char **env, t_data *data);

// char	*get_input(void);
// void	prompt(t_data *data);
#endif