/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/18 23:21:28 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/01 15:58:09 by fholwerd      ########   odam.nl         */
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

void	execute_child(t_commands *commands, t_metainfo *info)
{
	if (check_builtin(commands) == true)
	{
		execute_builtin(commands, info);
	}
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

static void	child_redirection(t_commands *commands, t_metainfo *info, int pipefd[2])
{
	if (commands->infile)
	{
		info->infilefd = open(commands->infile->name, commands->infile->mode);
		if (dup2(info->infilefd, STDIN_FILENO) == -1)
			dupe_error();
		close(info->infilefd);
	}
	if (commands->outfile)
	{
		info->outfilefd = open(commands->outfile->name, commands->outfile->mode);
		if (dup2(info->outfilefd, STDOUT_FILENO) == -1)
			dupe_error();
		close(info->outfilefd);
	}
	if (commands->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			dupe_error();
	}
}

int	execute_fork(t_commands *commands, t_metainfo *info)
{
	pid_t		pid;
	int			pipefd[2];

	info->path = find_path(info, commands);
	if (pipe(pipefd) == -1)
		pipe_error();
	pid = fork();
	if (pid == -1)
		fork_error();
	else if (pid == 0)
	{
		child_redirection(commands, info, pipefd);
		close(pipefd[0]);
		close(pipefd[1]);
		printf("closed child pipes of pipe %s\n", info->path);
		execute_child(commands, info);
	}
	close(pipefd[1]);
	if (commands->next && !commands->next->infile)
	{
		info->infilefd = pipefd[0];
		printf("new command found, no infile found, setting infile to pipe read end with fd %d\n", info->infilefd);
	}
	else
		close(pipefd[0]);
	return (pid);
}

char **executer(t_commands *commands, char **envp)
{
	bool		builtin;
	t_metainfo	*info;
	int i = 0;
	t_commands	*temp;

	info = malloc(sizeof(t_metainfo));
	info->envp = envp;
	temp = commands;
	if (temp->next == NULL)
	{
		printf("only one command found\n");
		builtin = check_builtin(temp);
		if (builtin == true)
			execute_builtin(temp, info);
		else
		{
			info->lastpid = execute_fork(temp, info);
			waitpid(info->lastpid, NULL, 0);
		}
	}
	else
		while (temp)
		{
			i++;
			printf("loop number: %d\n", i);
			info->lastpid = execute_fork(temp, info);
			printf("current lastpid = %d, about to move to next command\n", info->lastpid);
			temp = temp->next;
		}
	waitpid(info->lastpid, NULL, 0);
	return (info->envp);
}