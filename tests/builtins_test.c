#include "minishell.h"
#include "builtins.h"
#include "prompt.h"
#include "env_var.h"



t_cmd	*makeshift_parser(char *input);
void	run_cmd(t_ms *ms, t_cmd *cmd);

void	prompt(t_ms *ms)
{
	char	*input;
	t_cmd	*cmd;
	int		i;

	while (420)
	{
		i = 0;
		input = get_input();
		if (!input || !ft_strncmp(input, "exit", 4))
		{
			ft_putendl_fd("exit", 2);
			if (input)
				free(input);
			clear_history();
			break ;
		}
		cmd = makeshift_parser(input);
		free(input);
		run_cmd(ms, cmd);
		free(cmd);
	// 			else if (!ft_strncmp(input, "cd", 2))
	// 	{
	// 		if (ft_strlen(input) > 3)
	// 			builtin_cd(input+3, ms);
	// 		else
	// 			builtin_cd(NULL, ms);
	// 	}
	// 	else if (!ft_strncmp(input, "env", 3))
	// 		builtin_env(ms);
	// 	else if (!ft_strncmp(input, "pwd", 3))
	// 		builtin_pwd();
	// 	else if (!ft_strncmp(input, "export", 6))
	// 		builtin_export(ms, input+7);
	// 	else if (!ft_strncmp(input, "unset", 5))
	// 		builtin_unset(ms, input+6);
	// 	else if (input[0] != '\0' && input[0] != '\n')
	// 		ft_printf("%s: %s\n", input, CMD_NOT_FOUND);
	// 	free(input);
	}
}

void	run_cmd(t_ms *ms, t_cmd *cmd)
{
	char *ls[] = {"ls", ""};
	
	if (!ft_strcmp(cmd->cmd, "cd"))
		builtin_cd(ms, cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		builtin_pwd(cmd);
	else if (!ft_strcmp(cmd->cmd, "export"))
		builtin_export(ms, cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		builtin_env(ms);
	else if (!ft_strcmp(cmd->cmd, "echo"))
		builtin_echo(ms, cmd);
	else if (!ft_strncmp(cmd->cmd, "unset", 5))
		builtin_unset(ms, cmd);
}

t_cmd	*makeshift_parser(char *input)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	int	i = 0;
	int len = 0;
	int j = 0;

	cmd->argcount = 0;
	while(input[i++])
	{
		if (input[i] == ' ')
			cmd->argcount++;
	}
	i = 0;
	while (input[i] != ' ' && input[i] != '\0')
	{
		len++;
		i++;
	}
	len++;
	i++;
	cmd->cmd = malloc(sizeof(char) * len);
	ft_strlcpy(cmd->cmd, input, len);
	if (cmd->argcount > 0)
	{
		cmd->arg = malloc(sizeof(char) * cmd->argcount);
		while(input[i])
		{
			len = 0;
			while (input[i] != ' ' && input[i] != '\0')
			{
				len++;
				i++;
			}
			len++;
			i++;
			cmd->arg[j] = malloc(sizeof(char) * len);
			ft_strlcpy(cmd->arg[j], input + i - len, len);
			j++;
		}
	}
	return(cmd);
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
	ft_clear_evlist(ms);
	free(ms);
	return (0);
}