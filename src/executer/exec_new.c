/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_new.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 19:23:48 by ahorling      #+#    #+#                 */
/*   Updated: 2023/03/24 20:59:51 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "structs.h"
#include "executer/pathfind.h"
#include "executer/errors.h"
#include "executer/builtins.h"

static void	execute_child(t_commands *commands, t_metainfo *info)
{
	if (check_builtin(commands) == true)
		execute_builtin(commands, info);
	else if (access(commands->args[0], F_OK) == 0)
	{
		execve(commands->args[0], commands->args, info->envp);
		path_error();
	}
	else
	{
		execve(info->path, commands->args, info->envp);
		path_error();
	}
}

static void	child_redirects(t_commands *commands, t_metainfo *info, int pipe1[2], int pipe2[2])
{
	if (commands->prev && info->infilefd != STDIN_FILENO)
	{
		dup2(pipe1[0], info->infilefd);
		close(pipe1[0]);
		close(pipe1[1]);
	}
	else if ((commands->prev && info->infilefd == STDIN_FILENO) || commands->prev == NULL)
	{
		dup2(pipe1[0], STDIN_FILENO);
		close(pipe1[0]);
		close(pipe1[1]);
	}
	if (commands->next && info->outfilefd != STDOUT_FILENO)
	{
		close(pipe2[0]);
		dup2(pipe2[1], info->outfilefd);
		close(pipe2[1]);
	}
	else if (commands->next && info->outfilefd == STDIN_FILENO)
	{
		close(pipe2[0]);
		dupe2(pipe2[1], STDOUT_FILENO);
		close(pipe2[1]);
	}
	else if (commands->next == NULL)
	{
		close(pipe2[0]);
		close(pipe2[1]);
	}
}

static void	setup_info(t_commands *commands, t_metainfo *info)
{
	info->path = find_path(info, commands);
	if (commands->infile)
		if (commands->infile->mode2 == -1)
			info->infilefd = open(commands->infile->name, commands->infile->mode);
		else
			info->infilefd = open(commands->infile->name, commands->infile->mode2);
	else
		info->infilefd = STDIN_FILENO;
	if (commands->outfile)
		if (commands->outfile->mode2 == -1)
			info->outfilefd = open(commands->outfile->name, commands->outfile->mode);
		else
			info->outfilefd = open(commands->outfile->name, commands->outfile->mode2);
	else
		info->outfilefd = STDOUT_FILENO;
}

static int		begin_fork(t_commands *commands, t_metainfo *info)
{
	int		pipe1[2];
	int		pipe2[2];
	pid_t	pid;

	while (commands)
	{
		setup_info(commands, info);
		pipe(pipe1);
		if (commands->next)
			pipe(pipe2);
		pid = fork();
		if (pid == 0)
		{
			child_redirects(commands, info, pipe1, pipe2);
			execute_child(commands, info);
		}
		else
		{
			if (commands->prev)
			{
				close(pipe1[0]);
				close(pipe1[1]);
			}
			if (commands->next)
			{
				pipe1[0] = pipe2[0];
				pipe1[1] = pipe2[1];
			}
		}
		close(pipe1[0]);
		close(pipe1[1]);
	}
	return (pid);
}

void	executer(t_commands *commands, char **envp)
{
	t_metainfo	*info;

	info = malloc(sizeof(t_metainfo));
	info->envp = envp;
	if (commands->next == NULL)
	{
		if (check_builtin(commands) == true)
			execute_builtin(commands, info);
		else
		{
			info->lastpid = begin_fork(commands, info);
			waitpid(info->lastpid, NULL, 0);
		}
	}
	else
	{
		while(commands)
		{
			info->lastpid = begin_fork(commands, info);
			commands = commands->next;
		}
	}
	waitpid(info->lastpid, NULL, 0);
	return ;
}