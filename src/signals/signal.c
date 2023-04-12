/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 13:29:18 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/12 16:11:43 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "readline/readline.h"

void	termion(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
}

void	termioff(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
}

static void	redirect_int(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	redirect_signal(void)
{
	if (signal(SIGINT, redirect_int) == SIG_ERR)
		write(2, "Sigint error\n", 13);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		write(2, "Sigint error\n", 13);
}
