/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:58:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/08 17:57:33 by oandelin         ###   ########.fr       */
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
# include <signal.h>
# include <fcntl.h>

# define BYELLOW "\001\e[0;33m\002"
# define RESET   "\001\e[0m\002"

# define PROMPT  "minishell> "
# define CMD_NOT_FOUND "Command not found"

# define TRUNC_OUT 1
# define APPEND_OUT 2	
# define INPUT_FILE 1
# define INPUT_HEREDOC 2

int	g_sig_status;

enum e_errors {
	BAD_CMD = 1,
	MALLOC_FAIL = 2,
	PIPE_FAIL = 3,
	FORK_FAIL = 4,
	SYNTAX_ERROR = 5,
};

typedef struct s_dmh {
	char 			*mem_hold;
	struct s_dmh	*next;
} t_dmh;

typedef struct s_ev {
	char		*key;
	char		*value;
	struct s_ev	*next;
}	t_ev;

typedef struct s_token {
	int				type;
	char			*str;
	struct s_token	*next;
} t_token;

typedef struct s_exec{
	char	*cmd;
	char	**argv;
	int		read_fd;
	int		write_fd;
	int		has_heredoc;
	char	*heredoc;
	struct s_exec	*next;
	struct s_token	*token;
}				t_exec;

typedef struct s_lexer {
	char		*tmp_str;
	char		*exp;
	char		*exp_tmp;
	char		*exp_env;
	int			input_len;
	int			s_quote_open;
	int			d_quote_open;
	int			str_open;
	int			words;
	t_token		*token;
	t_dmh		*dmh_list;
} t_lexer;

typedef struct s_data {
	char	*input;
	t_lexer	lexer;
	t_ev	*env_var;
	t_exec	*exec;
	int		exit_status;
	struct termios		old_termios;
	struct termios		new_termios;
	struct sigaction	sa;
}	t_data;

void	rl_replace_line(const char *text, int clear_undo);

t_data	*init_data(void);
t_exec	*init_exec(void);
void	save_env_var(char **env, t_data *data);
char *expand_ev(t_data *data, char *line);

//		OUTPUT
void	ft_errormsg(int errorcode, char *cmd);

// char	*get_input(void);
// void	prompt(t_data *data);
#endif