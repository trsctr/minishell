/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:58:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/06 14:46:35 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define T_CMD			42
# define T_WORD			43
# define T_EMPTY_WORD	44
# define T_PIPE			45
# define T_RD_S_L		46
# define T_RD_S_R		47
# define T_RD_D_L		48
# define T_RD_D_R		49

# include <readline/readline.h>
# include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libft/libft.h"

typedef struct s_token {
	int				type;
	char			*str;
	struct s_token	*next;
} t_token;

/* typedef struct s_ev {
	char		*key;
	char		*value;
	struct s_ev	*next;
}	t_ev; */

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
} t_lexer;

typedef struct s_data {
	char		*input;
	//t_ev		*env_var;
	t_lexer 	lexer;
} t_data;

/* lexer */

void		init_data_lexer(t_data *data);
int			empty_word(t_data *data, int i);
char		quote_status(t_data *data);
void		open_close_quotes(t_data *data, char c);
int			handle_quotes(t_data *data, int i);
int			handle_words(t_data *data, int i);
void		split_input_words(t_data *data);
void		tokenize(t_data *data, int type, char *str);
void		fill_node(t_token **token, int type, char *str);
int			check_executable(char *word);
int			check_executable_test(char *word, char *part, int i, int j);

void		exit_error(t_data *data, char *error);
void		print_token(t_token *token);
char 		*get_input(void);
void		prompt(t_data *data);

#endif