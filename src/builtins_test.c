#include "minishell.h"
#include "builtins.h"
#include "prompt.h"
#include "env_var.h"

void	prompt(t_data *data)
{
	char	*input;

	while (420)
	{
		input = get_input();
		if (!input || !ft_strncmp(input, "exit", 4))
		{
			ft_putendl_fd("exit", 2);
			if (input)
				free(input);
			//ft_lstclear(&data->env_var, &free);
			//free(data);
			clear_history();
			break ;
		}
		else if (!ft_strncmp(input, "cd", 2))
		{
			if (ft_strlen(input) > 3)
				builtin_cd(input+3, data);
			else
				builtin_cd(NULL, data);
		}
		else if (!ft_strncmp(input, "env", 3))
			builtin_env(data);
		else if (!ft_strncmp(input, "pwd", 3))
			builtin_pwd();
		else if (!ft_strncmp(input, "export", 6))
			builtin_export(data, input+7);
		else if (!ft_strncmp(input, "unset", 5))
			builtin_unset(data, input+6);
		else if (input[0] != '\0' && input[0] != '\n')
			ft_printf("%s: %s\n", input, CMD_NOT_FOUND);
		free(input);
	}
}

char	*get_input(void)
{
	char				*line;

	toggle_echoctl();
	listen_signals();
	line = readline(BYELLOW PROMPT RESET);
	if (!line)
	{
		toggle_echoctl();
		reset_signals();
		return (NULL);
	}
	if (line[0] != '\0' && line[0] != '\n')
		add_history(line);
	toggle_echoctl();
	reset_signals();
	return (line);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->env_var = NULL;//malloc(sizeof(t_ev));
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void) ac;
	(void) av;
	data = init_data();
	save_env_var(env, data);
	prompt(data);
	return (0);
}