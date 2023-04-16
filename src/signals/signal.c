/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 13:29:18 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/16 17:06:12 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "readline/readline.h"

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

static void	redirect_hd_int(int signal)
{
	if (signal == SIGINT)
		write(1, "\n", 1);
}

void	redirect_signal(int mode)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		write(2, "Sigquit error\n", 14);
	if (mode == 0)
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
			write(2, "Sigint error\n", 13);
	}
	else if (mode == 1)
	{
		if (signal(SIGINT, redirect_int) == SIG_ERR)
			write(2, "Sigint error\n", 13);
	}
	else if (mode == 2)
	{
		if (signal(SIGINT, redirect_hd_int) == SIG_ERR)
			write(2, "Sigint error\n", 13);
	}
	else if (mode == 3)
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			write(2, "Sigint error\n", 13);
	}
	else if (mode == 4)
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
			write(2, "Sigint error\n", 13);
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			write(2, "Sigquit error\n", 14);
	}
}
