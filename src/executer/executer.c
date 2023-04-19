/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 19:23:48 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/19 18:06:46 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "builtins.h"
#include "errors.h"
#include "extra.h"
#include "pathfind.h"
#include "signal.h"
#include "termine.h"
#include "structs.h"
#include "termine.h"

extern int	g_error;

static void	execute_child(t_commands *commands, t_metainfo *info)
{
	if (check_builtin(commands) == true)
		execute_builtin(commands, info);
	else if (access(commands->args[0], F_OK) == 0)
	{
		execve(commands->args[0], commands->args, info->envp);
		path_error(commands);
	}
	else
	{
		execve(info->path, commands->args, info->envp);
		path_error(commands);
	}
}

static void	child_redirects(t_commands *commands, t_metainfo *info, int pipe1[2], int pipe2[2])
{
	if (info->infilefd != STDIN_FILENO)
	{
		dup2(info->infilefd, STDIN_FILENO);
		close(info->infilefd);
		if (commands->prev)
			close_pipes(pipe1);
	}
	else if (commands->prev)
	{
		dup2(pipe1[0], STDIN_FILENO);
		close_pipes(pipe1);
	}
	if (info->outfilefd != STDOUT_FILENO)
	{
		dup2(info->outfilefd, STDOUT_FILENO);
		close(info->outfilefd);
		if (commands->next)
			close_pipes(pipe2);
	}
	else if (commands->next)
	{
		dup2(pipe2[1], STDOUT_FILENO);
		close_pipes(pipe2);
	}
}

static void	setup_info(t_commands *commands, t_metainfo *info)
{
	info->path = find_path(info, commands);
	manage_infiles(commands, info);
	manage_outfiles(commands, info);
	if (g_error != 0)
		exit(g_error);
}

static int	begin_fork(t_commands *commands, t_metainfo *info, int pipe1[2], int pipe2[2])
{
	pid_t	pid;

	if (commands->next)
		pipe(pipe2);
	pid = fork();
	if (pid < 0)
		fork_error();
	if (pid == 0)
	{
		redirect_signal(4);
		setup_info(commands, info);
		child_redirects(commands, info, pipe1, pipe2);
		execute_child(commands, info);
	}
	else
	{
		if (commands->prev)
			close_pipes(pipe1);
		if (commands->next)
		{
			pipe1[0] = pipe2[0];
			pipe1[1] = pipe2[1];
		}
	}
	return (pid);
}

char	**executer(t_commands *commands, char **envp)
{
	t_metainfo	*info;
	int			pipe1[2];
	int			pipe2[2];
	int			status;
	char		**envret;

	status = 0;
	info = malloc(sizeof(t_metainfo));
	info->envp = envp;
	if (commands && commands->next == NULL)
	{
		if (check_builtin(commands) == true)
		{
			execute_builtin(commands, info);
			free(info->path);
			closefds(info);
			envret = info->envp;
			free(info);
			return (envret);
		}
		else
		{
			termioff();
			info->lastpid = begin_fork(commands, info, pipe1, pipe2);
			waitpid(info->lastpid, &status, 0);
		}
	}
	else
	{
		while (commands)
		{
			termioff();
			info->lastpid = begin_fork(commands, info, pipe1, pipe2);
			if (commands->next == NULL)
				break ;
			commands = commands->next;
		}
	}
	if (commands->prev)
		close_pipes(pipe1);
//	waitpid(info->lastpid, &status, 0);
	while (info->lastpid == wait(&status) > 0);
	if (WIFEXITED(status) == true)
		status = WEXITSTATUS(status);
	g_error = status;
	termion();
	closefds(info);
	envret = info->envp;
	free(info);
	return (envret);
}
