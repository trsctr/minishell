/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:58:52 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/08 21:58:05 by oandelin         ###   ########.fr       */
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* lexer_dmh.c */

t_dmh	*dmh_new(t_data *data, size_t size);
char	*dmh(t_data *data, size_t size);
void	free_list_dmh(t_data *data);

/* lexer_executables.c */

int		check_executable(t_data *data);

t_token	*check_token_redirect(t_data *data, t_token *tmp);
void	check_token(t_data *data);

/* lexer_expandables.c */

int		check_question_mark(t_data *data, int i);
int		fill_exp_from_middle(t_data *data, int i, int j);
int		fill_exp_from_start(t_data *data, int i);
int		fill_expandable(t_data *data, int i);
void	check_expandable(t_data *data, int start, int len);

/* lexer_libft_mods */

char	*ft_strdup_dmh(t_data *data, const char *s1);
char	*ft_strndup_dmh(t_data *data, const char *s1, size_t n);
char	*ft_strjoin_dmh(t_data *data, char const *s1, char const *s2);

/* lexer_pipes_redirects.c */

int		redirect_solver(t_data *data, int i);
int		handle_pipes_redirects(t_data *data, int i);

/* lexer_specials.c */

int		check_syntax(t_data *data);
void	init_data_lexer(t_data *data);
int		handle_spaces(t_data *data, int i);
void	free_list_token(t_data *data);

/* lexer_tokenizer.c */

void	fill_node(t_data *data, t_token **token, int type, char *str);
void	tokenize(t_data *data, int type, char *str);

/* lexer_words_utils.c */

char	quote_status(t_data *data);
void	open_close_quotes(t_data *data, char c);
int		empty_word(t_data *data, int i);

/* lexer_words.c */

int		handle_words_unquoted(t_data *data, int i);
int		handle_words_d_quoted(t_data *data, int i);
int		handle_words_s_quoted(t_data *data, int i);
int		handle_quotes(t_data *data, int i);

/* lexer.c */

int		handle_specials(t_data *data, int i);
void	lexer(t_data *data);


/* naa romut pois*/

void		malloc_error(t_data *data);
void		ft_errormsg(int errorcode, char *cmd);

#endif