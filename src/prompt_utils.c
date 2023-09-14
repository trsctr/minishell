/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:06:29 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/14 13:49:44 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"

/**
 * @brief sets up terminal and signals for our minishell session and saves original
 * settings to our struct so they can be restored when exiting, and also
 * in the end of loop to avoid some hiccups if user happens to run top and
 * exits from it abruptly
 * 
 * @param data 
 */
void	terminal_setup(t_data *data)
{
	tcgetattr(STDIN_FILENO, &(data->old_termios));
	data->new_termios = data->old_termios;
	data->new_termios.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &(data->new_termios));
	sigemptyset(&(data->sa.sa_mask));
	data->sa.sa_sigaction = &handle_sig_int;
	sigaction(SIGINT, &(data->sa), NULL);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief resets signal listening to original settings so child processes can
 * listen to signals normally
 * 
 */
void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief resets terminal settings
 * 
 * @param data 
 */
void	terminal_reset(t_data *data)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(data->old_termios));
}

/**
 * @brief this function is called if user presses ctrl+c when in command prompt
 * in this case we ignore what user has written and display a new command line
 * 
 * @param signal 
 */
void	handle_sig_int(int signal, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signal == SIGINT)
	{
		g_sig_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**
 * @brief checks if the line received from user is not just full of spaces
 * 
 * @param line 
 * @return int 0 if only spaces, 1 if there is something else too
 */
int	only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n' && line[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}
