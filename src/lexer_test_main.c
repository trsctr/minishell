#include "lexer.h"
#include <stdio.h>

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
		if (!ft_strncmp(data->input, "exit", 4))
		{
			ft_putendl_fd("exit", 2);
			clear_history();
			free(data->input);
			break ;
		}
		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n\n\n\n");
		lexer(data);
		print_token(data->lexer.token);
		free_list_token(data);
		free(data->input);
	}
}

t_data	*init_data()
{
	t_data *data;
	
	data = malloc(sizeof(t_data) * 1);
	data->lexer.dmh_list = NULL;
	data->exit_status = 0;
	return(data);
}

int	main(int ac, char **av, char **env)
{
	t_data *data;
	
	(void) ac;
	(void) av;
	(void) env;
	data = init_data();
	printf("Welcome to minishell\nPlease enter your command below\n\n");
	prompt(data);
	free_list_dmh(data);
	free(data);
	return(0);
}