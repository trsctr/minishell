/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:06:29 by oandelin          #+#    #+#             */
/*   Updated: 2023/08/25 16:03:23 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"

/**
 * @brief sets up signal listening. ctrl+\ will be ignored. ctrl+c will be
 * handled by handle_sig_int
 * 
 */
void	listen_signals(void)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGQUIT);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
	signal(SIGINT, handle_sig_int);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief this resets signal handling to normal settings
 * 
 */
void	reset_signals(void)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGQUIT);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
	signal(SIGINT, handle_sig_int);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief this function is called if user presses ctrl+c when in command prompt
 * in this case we ignore what user has written and display a new command line
 * 
 * @param signal 
 */
void	handle_sig_int(int signal)
{
	(void) signal;
	write(1, "\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief this function is called in the beginning and end of get_input
 * it toggles the status of ECHOCTL in terminal settings. we don't want to
 * display control characters (such as ^C or ^\) in the command prompt, but
 * it is good to also reset the terminal settings.
 * 
 */
void	toggle_echoctl(void)
{
	struct termios	termios_attributes;

	tcgetattr(STDIN_FILENO, &termios_attributes);
	termios_attributes.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_attributes);
}
