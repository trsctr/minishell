/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:12:38 by oandelin          #+#    #+#             */
/*   Updated: 2023/09/18 18:12:44 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief sets up terminal and signals for our minishell session and saves
 * original settings to our struct so they can be restored when exiting, and also
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
	data->sa.sa_sigaction = &handle_sig_in_terminal;
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
void	handle_sig_in_terminal(int signal, siginfo_t *info, void *context)
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

void	handle_sig_in_exec(int signal, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signal == SIGINT)
	{
		g_sig_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
