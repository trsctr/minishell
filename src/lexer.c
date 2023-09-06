/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:45 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/06 17:21:08 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*	*split_input:
*	Splits given input into words to char**.
*	Word separation is done by space or looking for second quote (" or ') 
*	after first one, if they aren't located already between quotes.
*	Also valid redirects (>, <, >>, <<) and pipe (|) will separate words (even
*	if they aren't separated by space) unless they are located between quotes.
*/

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *new;

	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

void	exit_error(t_data *data, char *error)
{
	printf("%s\n", error);
	(void)data;
	exit(1);
}

void	print_token(t_token *token)
{
	while(token)
	{
		printf("- - - - - - - - - - - - - - - - - - \n");
		if(token->type == 42)
        	printf("Type: CMD\n");
		else if(token->type == 43)
        	printf("Type: WORD\n");
		else if(token->type == 44)
        	printf("Type: EMPTY WORD\n");
		else if(token->type == 45)
        	printf("Type: PIPE\n");
		else
			printf("Type: REDIRECT\n");
        printf("Output: %s\n", token->str);
		printf("- - - - - - - - - - - - - - - - - - \n");
        token = token->next;
		printf("\n\n");
	}
}
char *get_input(void)
{
	char	*line;

	line = readline("minishell :");
	if (line[0] != '\0' && line[0] != '\n')
		add_history(line);
	return (line);
}

void	prompt(t_data *data)
{

	while (420)
	{
		data->input = get_input();

		// split_input(input);

		if (!ft_strncmp(data->input, "exit", 4))
		{
			ft_putendl_fd("exit", 2);
			clear_history();
			break ;
		}
		//if (data->input[0] != '\0' && data->input[0] != '\n')
			//ft_printf("%s: command not found\n", data->input);
		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n\n\n\n");
		init_data_lexer(data);
		split_input_words(data);
		print_token(data->lexer.token);
	}
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



void	init_data_lexer(t_data *data)
{
    data->lexer.tmp_str = NULL;
	data->lexer.exp = NULL;
	data->lexer.exp_tmp = NULL;
	data->lexer.exp_env = NULL;
	data->lexer.input_len = 0;
	data->lexer.s_quote_open = 0;
	data->lexer.d_quote_open = 0;
    data->lexer.str_open = 0;
	data->lexer.words = 0;
	data->lexer.token = NULL;

	while(data->input[data->lexer.input_len])
	{
		data->lexer.input_len++;
	}
}

int	fill_exp_from_middle(t_data *data, int i, int j)
{
	int new_i;

	data->lexer.exp_tmp = ft_strndup(data->lexer.exp, j);
		if(data->lexer.exp_env != NULL)
		{
			data->lexer.exp_tmp = ft_strjoin_free(data->lexer.exp_tmp,
				data->lexer.exp_env);
			new_i = ft_strlen(data->lexer.exp_tmp);
			data->lexer.exp_tmp = ft_strjoin_free(data->lexer.exp_tmp,
				ft_strdup(data->lexer.exp + i));
		}
		else
		{
			new_i = ft_strlen(data->lexer.exp_tmp);
			data->lexer.exp_tmp = ft_strjoin_free(data->lexer.exp_tmp,
				ft_strdup(data->lexer.exp + i));
		}
	return (new_i);
}

int	fill_exp_from_start(t_data *data, int i)
{
	int new_i;

	if(data->lexer.exp_env != NULL)
		{
			data->lexer.exp_tmp = ft_strdup(data->lexer.exp_env);
			new_i = ft_strlen(data->lexer.exp_tmp);
			data->lexer.exp_tmp = ft_strjoin_free(data->lexer.exp_tmp,
				ft_strdup(data->lexer.exp + i));
		}
		else
		{
			new_i = 0;
			data->lexer.exp_tmp = ft_strdup(data->lexer.exp + i);
		}
		free(data->lexer.exp_env);
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
			data->lexer.exp_tmp = ft_strndup(data->lexer.exp + j, i - j);
			if(getenv(data->lexer.exp_tmp) == NULL)
				data->lexer.exp_env = NULL;
			else
				data->lexer.exp_env = ft_strdup(getenv(data->lexer.exp_tmp));	// korvaa omalla vastaavalla
			free(data->lexer.exp_tmp);
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
	data->lexer.exp = ft_strndup(data->input + start, len);
	while(data->lexer.exp[i])
	{
		if(data->lexer.exp[i] == '$')
		{
			while(data->lexer.exp[i] == '$')
				i++;
			if(data->lexer.exp[i] == ' ' || data->lexer.exp[i] == '\t'
				|| data->lexer.exp[i] == '\0')
				continue;
			i = fill_expandable(data, i);
			free(data->lexer.exp);
			data->lexer.exp = ft_strdup(data->lexer.exp_tmp);
			free(data->lexer.exp_tmp);
		}
		else
			i++;
	}
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



int	check_executable_test(char *word, char *part, int i, int j)
{
	char *res;

	res = malloc(sizeof(char) * (ft_strlen(word) + ft_strlen(part) + 2));
	if(res == NULL)
		exit_error(NULL, "malloc error\n");						// kayta oikeaa exit error
	while(part[++i])
		res[i] = part[i];
	res[i] = '/';
	i++;
	while(word[j])
	{
		res[i] = word[j];
		i++;
		j++;
	}
	res[i] = '\0';
	if(access(res, X_OK) == 0)
	{
		free(res);
		return(1);
	}
	free(res);
	return(0);
}

int	check_executable(char *word)
{
	char	*path;
	int	start;
	int	result;
	int	i;

	result = 0;
	i = 0;
	if(!ft_strcmp(word, "echo") || !ft_strcmp(word, "cd")
	|| !ft_strcmp(word, "pwd") || !ft_strcmp(word, "export")
	|| !ft_strcmp(word, "unset") || !ft_strcmp(word, "env")
	|| !ft_strcmp(word, "exit"))
		return (1);
	path = getenv("PATH");										// korvaa omalla vastaavalla
	if(path == NULL)
		exit_error(NULL, "failed to get path\n");				// kayta oikeaa exit error
	while(path[i])
	{
		start = i;
		while(path[i] != ':' && path[i] != '\0')
			i++;
		result += check_executable_test(word, ft_strndup(path + start, i - start), -1, 0);
        if(path[i] == ':')
            i++;
	}
	return(result);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int	empty_word(t_data *data, int i)
{
    int count;
	
	count = 0;
	if (data->lexer.input_len - i > 1
	    && (data->input[i] == '\'' || data->input[i] == '\"'))
    {
        if (i != 0 && data->input[i - 1] != ' ' && data->input[i - 1] != '\t')
            return (0);
        while (data->input[i] == '\'' || data->input[i] == '\"')
		{
			if (data->input[i + 1] == data->input[i])
			{
				i += 2;
				count += 2;
			}
			else
				return (0);
		}
        if (data->input[i] == '\0' || data->input[i] == ' ')
			return (count);
    }
    return (0);
}

char	quote_status(t_data *data)
{
	if (data->lexer.s_quote_open == 1)
		return ('\'');
	else if(data->lexer.d_quote_open == 1)
		return ('\"');
	else
		return (0);
}

void	open_close_quotes(t_data *data, char c)
{
	if (c == '\'' && data->lexer.d_quote_open == 0)
	{
		if (data->lexer.s_quote_open == 1)
			data->lexer.s_quote_open = 0;
		else
			data->lexer.s_quote_open = 1;
	}
	if (c == '\"' && data->lexer.s_quote_open == 0)
	{
		if (data->lexer.d_quote_open == 1)
			data->lexer.d_quote_open = 0;
		else
			data->lexer.d_quote_open = 1;
	}
}

void	fill_node(t_token **token, int type, char *str)
{
	t_token	*new;
	t_token *tmp;

	new = malloc(sizeof * new);
	if (!new)
		exit_error(NULL, "malloc error\n");			// kayta oikeaa exit error
	new->type = type;
	new->str = str;
	new->next = NULL;
	if (*token == NULL)
		*token = new;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	tokenize(t_data *data, int type, char *str)
{
	if(type == T_WORD && check_executable(str))
		type = T_CMD;
	fill_node(&data->lexer.token, type, str);
	data->lexer.tmp_str = NULL;
}

int handle_words_d_quoted(t_data *data, int i)
{
	char *tmp_for_tmp_str;
    int start;

    start = i;
    while(data->input[i] != quote_status(data))
    {
        if(!data->input[i])
            exit_error(data, "quotes open\n");		// kayta oikeaa exit error
        i++;
    }
    data->lexer.str_open = 1;
    check_expandable(data, start, i - start);
	if(data->lexer.tmp_str == NULL)
        data->lexer.tmp_str = ft_strdup(data->lexer.exp);
    else
	{
		tmp_for_tmp_str = ft_strdup(data->lexer.tmp_str);
		free(data->lexer.tmp_str);
		data->lexer.tmp_str = ft_strjoin(tmp_for_tmp_str, data->lexer.exp);
		free(tmp_for_tmp_str);
	}
	free(data->lexer.exp);
    open_close_quotes(data, data->input[i]);
    return(i + 1);
}

int handle_words_s_quoted(t_data *data, int i)
{
	char *tmp_for_tmp_str;
    int start;

    start = i;
    while(data->input[i] != quote_status(data))
    {
        if(!data->input[i])
            exit_error(data, "quotes open\n");		// kayta oikeaa exit error
        i++;
    }
    data->lexer.str_open = 1;
    if(data->lexer.tmp_str == NULL)
        data->lexer.tmp_str = ft_strndup(data->input + start, i - start);
    else
	{
		tmp_for_tmp_str = ft_strdup(data->lexer.tmp_str);
		free(data->lexer.tmp_str);
        data->lexer.tmp_str = ft_strjoin(tmp_for_tmp_str, ft_strndup(data->input + start, i - start));
		free(tmp_for_tmp_str);
	}
    open_close_quotes(data, data->input[i]);
    return(i + 1);
}

int	handle_words_unquoted(t_data *data, int i)
{
	char *tmp_for_tmp_str;
	int start;
	
    start = i;
    while(data->input[i] != '\'' && data->input[i] != '\"'
		&& data->input[i] != ' ' && data->input[i] != '\t'
		&& data->input[i] != '|' && data->input[i] != '>'
		&& data->input[i] != '<' && data->input[i] != '\0')
			i++;
	data->lexer.str_open = 1;
	check_expandable(data, start, i - start);
	if(data->lexer.tmp_str == NULL)
        data->lexer.tmp_str = ft_strdup(data->lexer.exp);
    else
	{
		tmp_for_tmp_str = ft_strdup(data->lexer.tmp_str);
		free(data->lexer.tmp_str);
		data->lexer.tmp_str = ft_strjoin(tmp_for_tmp_str, data->lexer.exp);
		free(tmp_for_tmp_str);
	}
	free(data->lexer.exp);
	return(i);
}

int	handle_quotes(t_data *data, int i)
{
	if(empty_word(data, i) && !quote_status(data))
	{
		tokenize(data, T_EMPTY_WORD, ft_strndup(data->input + i, empty_word(data, i)));
		return (i + empty_word(data, i));
	}
    else if(data->input[i] == data->input[i + 1])
        return (i + 2);
	else
	{
		open_close_quotes(data, data->input[i]);
		if(data->input[i] == '\'')
        	return(handle_words_s_quoted(data, i + 1));
		else
			return(handle_words_d_quoted(data, i + 1));
	}
}

int	redirect_helper(t_data *data, int i)
{
	int j;

	j = i;

	while(data->input[j] == '>' || data->input[j] == '<')
			j++;
	if(j - i > 2 || (j - i == 2 && data->input[i] != data->input[i + 1]))
		exit_error(data, "syntax redirects\n");									// kayta oikeaa exit error
	if(j - i == 1 && data->input[i] == '<')
		tokenize(data, T_RD_S_L, "<");
	if(j - i == 1 && data->input[i] == '>')
		tokenize(data, T_RD_S_R, ">");
	if(j - i == 2 && data->input[i] == '<')
		tokenize(data, T_RD_D_L, "<<");
	if(j - i == 2 && data->input[i] == '>')
		tokenize(data, T_RD_D_R, ">>");
	return(j);
}

int	handle_pipes_redirects(t_data *data, int i)
{
	int j;

	j = i;
	if(data->lexer.str_open == 1)
    {
        tokenize(data, T_WORD, data->lexer.tmp_str);
        data->lexer.str_open = 0;
    }
	if(data->input[i] == '>' || data->input[i] == '<')
	{
		i = redirect_helper(data, i);
		return (i);
	}
	if(data->input[i + 1] == '|')
		exit_error(data, "syntax pipes\n");											// kayta oikeaa exit error
	tokenize(data, T_PIPE, "|");
	return(i + 1);
}

int		handle_spaces(t_data *data, int i)
{
	if(data->lexer.str_open == 1)
    {
        tokenize(data, T_WORD, data->lexer.tmp_str);
        data->lexer.str_open = 0;
    }
		while(data->input[i] == ' ' || data->input[i] == '\t')
			i++;
	return (i);
}

void	split_input_words(t_data *data)
{
	int i;

	i = 0;
	while(data->input[i])
	{
        if(data->input[i] == '\'' || data->input[i] == '\"')
		{
			i = handle_quotes(data, i);
			continue;
		}
		if((data->input[i] == ' ' || data->input[i] == '\t'))
		{
            i = handle_spaces(data, i);
			continue;
		}
		if(data->input[i] == '>' || data->input[i] == '<' || data->input[i] == '|')
		{
			i = handle_pipes_redirects(data, i);
			continue;
		}
		i = handle_words_unquoted(data, i);		
	}
	if(data->lexer.str_open == 1 && data->lexer.tmp_str[0] != '\0') 
		tokenize(data, T_WORD, data->lexer.tmp_str);
}

// muista open quotes check loppuun
// Kysy getenv asia liittyen executable ja expandable testiin etta voiko kayttaa jos env_var lista paivitetty minishellin sisalla etta pitaako kayttaa jotain omaa
// muista kaikki ft_strdup & strjoin etta malloc checkit niiden jalkeen

int	main(int ac, char **av, char **env)
{
	t_data *data;
	
	data = malloc(sizeof(t_data) * 1);
	//data->input = NULL;
	(void) ac;
	(void) av;
	(void) env;

	printf("Welcome to minishell\nPlease enter your command below\n\n");
	prompt(data);

	return(0);
}
