/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:58:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/15 14:49:50 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/include/libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
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
	EXPORT_NOT_VALID = 6,
	EXIT_BAD_VALUE = 7,
	FILE_NOT_FOUND = 8,
	CMD_IS_DIR = 9,
	EXEC_FAIL = 10,
};

typedef struct s_dmh {
	char			*mem_hold;
	struct s_dmh	*next;
}	t_dmh;

typedef struct s_ev {
	char		*key;
	char		*value;
	struct s_ev	*next;
}	t_ev;

typedef struct s_token {
	int				type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_exec{
	char			*cmd;
	char			**argv;
	int				read_fd;
	int				write_fd;
	int				has_heredoc;
	char			*heredoc;
	pid_t			pid;
	struct s_exec	*next;
	t_token			*token;
}	t_exec;

typedef struct s_lexer {
	char		*tmp_str;
	char		*exp;
	char		*exp_tmp;
	char		*exp_env;
	int			input_len;
	int			s_quote_open;
	int			d_quote_open;
	int			str_open;
	int			syntax_error;
	int			rd_flag;
	int			cmd_flag;
	int			pipe_flag;
	t_token		*token;
	t_dmh		*dmh_list;
}	t_lexer;

typedef struct s_data {
	char				*input;
	t_lexer				lexer;
	t_ev				*env_var;
	t_exec				*exec;
	int					exit_status;
	struct termios		old_termios;
	struct termios		new_termios;
	struct sigaction	sa;
}	t_data;

void	rl_replace_line(const char *text, int clear_undo);

//	INIT
t_data	*init_data(void);
t_exec	*init_exec(void);

// ENV VARS
char	*get_ev_key(char *str);
char	*get_ev_value(char *str);
char	*get_var_key(char *str);
char	*update_shlvl(char *value);
void	no_env_vars(t_data *data);
void	save_env_var(char **env, t_data *data);
int		key_is_valid(char *key);
char	*ft_getenv(t_data *data, char *key);

t_ev	*ft_new_evnode(char *key, char *value);
void	ft_new_env_var(t_ev **vars, t_ev *new_var);
t_ev	*ft_find_var(t_ev **vars, char *key);
void	ft_delete_var(t_ev **vars, char *key);
void	ft_change_var(t_ev **vars, char *key, char *value);
int		ft_envsize(t_ev *lst);

// PROMPT, TERMINAL, SIGNALS
void	terminal_setup(t_data *data);
void	terminal_reset(t_data *data);
void	handle_sig_int(int signal, siginfo_t *info, void *context);
void	reset_signals(void);
void	prompt(t_data *data);
char	*get_input(t_data *data);
int		only_spaces(char *line);
void	run_command_line(t_data *data);

// EXECUTION
int		executor(t_data *data, t_exec *exec);
int		is_builtin(char *cmd);
void	run_builtin(t_exec *exec, int spec, t_data *data);
void	find_n_exec(t_exec *exec, t_data *data);
int		is_abs_path(char *src);
char	*get_cmd_path(char *path_line, char *cmd);
int		cmd_is_dir(t_exec *exec);

// BUILTINS
void	builtin_env(t_data *data, t_exec *exec);
void	builtin_pwd(t_data *data, t_exec *exec);
void	builtin_cd(t_data *data, t_exec *exec);
void	builtin_export(t_data *data, t_exec *exec);
void	builtin_unset(t_data *data, t_exec *exec);
void	builtin_echo(t_data *data, t_exec *exec);
void	builtin_exit(t_data *data, t_exec *exec);

// HEREDOC
int		create_heredoc(t_data *data, t_exec *exec, t_token *token);
int		name_heredoc(t_exec *exec);
int		handle_heredocs(t_data *data);
int		redir_heredoc(t_data *data, t_exec *exec, t_token *token);
int		heredoc_loop(t_data *data, char *delim, int fd);
void	heredoc_handle_line(t_data *data, char *line, int fd);
int		expand_var_in_heredoc(t_data *data, char *line, int fd);

//	ERROR AND CLEANUP
void	malloc_error(t_data *data);
void	ft_errormsg(int errorcode, char *cmd);
void	set_exit_status(t_data *data, int status);
void	clear_data(t_data *data);
void	ft_clear_evlist(t_data *data);
void	free_array(char **array);
void	free_exec(t_exec *exec);

#endif