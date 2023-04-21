/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 21:12:10 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/21 20:58:14 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "builtins.h"
#include "errors.h"
#include "extra_utils.h"
#include "pathfind.h"
#include "signal.h"
#include "termine.h"
#include "structs.h"
#include "termine.h"
#include "executer.h"

extern int	g_error;

char	**exec_single_builtin(t_commands *commands, t_metainfo *info)
{
	char	**ret;

	g_error = 0;
	execute_builtin(commands, info);
	free(info->path);
	closefds(info);
	ret = info->envp;
	free(info);
	return (ret);
}

void	exec_single_command(t_commands *commands, t_metainfo *info
	, int pipe1[2], int pipe2[2])
{
	g_error = 0;
	termioff();
	info->lastpid = begin_fork(commands, info, pipe1, pipe2);
}

void	exec_multiple_commands(t_commands *commands, t_metainfo *info
	, int pipe1[2], int pipe2[2])
{
	g_error = 0;
	while (commands)
	{
		termioff();
		info->lastpid = begin_fork(commands, info, pipe1, pipe2);
		if (commands->next == NULL)
			break ;
		commands = commands->next;
	}
	if (commands->prev)
		close_pipes(pipe1);
}

int	get_exit_code(t_metainfo *info, int status)
{
	waitpid(info->lastpid, &status, 0);
	while (wait(NULL) > 0)
		continue ;
	if (WIFEXITED(status) == true)
	{
		status = WEXITSTATUS(status);
		termion();
		return (status);
	}
	termion();
	return (status);
}
