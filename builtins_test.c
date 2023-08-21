#include "minishell.h"
#include "builtins.h"
#include "prompt.h"
#include "env_var.h"

void	prompt(t_ms *ms)
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
			//ft_lstclear(&ms->env_var, &free);
			//free(ms);
			clear_history();
			break ;
		}
		else if (!ft_strncmp(input, "cd", 2))
		{
			if (ft_strlen(input) > 3)
				builtin_cd(input+3, ms);
			else
				builtin_cd(NULL, ms);
		}
		else if (!ft_strncmp(input, "env", 3))
			builtin_env(ms);
		else if (!ft_strncmp(input, "pwd", 3))
			builtin_pwd();
		else if (!ft_strncmp(input, "export", 6))
			builtin_export(ms, input+7);
		else if (!ft_strncmp(input, "unset", 5))
			builtin_unset(ms, input+6);
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

t_ms	*init_ms(void)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	ms->env_var = NULL;//malloc(sizeof(t_ev));
	return (ms);
}

int	main(int ac, char **av, char **env)
{
	t_ms	*ms;

	(void) ac;
	(void) av;
	ms = init_ms();
	save_env_var(env, ms);
	prompt(ms);
	return (0);
}