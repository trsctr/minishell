#include "minishell.h"
#include "executor.h"
#include "builtins.h"
#include "prompt.h"
#include "env_var.h"



t_exec	*makeshift_parser(char *input);

void	run_cmd(t_data *data, t_exec *exec);

void	prompt(t_data *data)
{
	char	*input;
	t_exec	*exec;
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
		exec = makeshift_parser(input);
		free(input);
		if (is_builtin(exec->cmd))
			run_builtin(exec, is_builtin(exec->cmd), data);
		else 
			executor(data, exec);
		free(exec);
	}
}

// void	run_cmd(t_data *data, t_cmd *cmd)
// {
// 	char *ls[] = {"ls", ""};
	
// 	if (!ft_strcmp(cmd->cmd, "cd"))
// 		builtin_cd(ms, cmd);
// 	else if (!ft_strcmp(cmd->cmd, "pwd"))
// 		builtin_pwd(cmd);
// 	else if (!ft_strcmp(cmd->cmd, "export"))
// 		builtin_export(ms, cmd);
// 	else if (!ft_strcmp(cmd->cmd, "env"))
// 		builtin_env(ms);
// 	else if (!ft_strcmp(cmd->cmd, "echo"))
// 		builtin_echo(ms, cmd);
// 	else if (!ft_strncmp(cmd->cmd, "unset", 5))
// 		builtin_unset(ms, cmd);
// }

t_exec	*makeshift_parser(char *input)
{
	t_exec *exec = malloc(sizeof(t_exec));
	int	i = 0;
	int len = 0;
	int j = 0;
	int argcount;

	while(input[i++])
	{
		if (input[i] == ' ')
			argcount++;
	}
	i = 0;
	while (input[i] != ' ' && input[i] != '\0')
	{
		len++;
		i++;
	}
	len++;
	i++;
	exec->cmd = malloc(sizeof(char) * len);
	ft_strlcpy(exec->cmd, input, len);
	exec->argv = ft_split(input, ' ');
	return(exec);
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
	data->env_var = NULL;
	data->exec = NULL;//malloc(sizeof(t_ev));
	return (data);
}

int	main(void)
{
	t_data		*data;
	extern char	**environ;

	data = init_data();
	save_env_var(environ, data);
	prompt(data);
	exit (0);
}