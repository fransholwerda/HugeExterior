/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/18 23:21:28 by ahorling      #+#    #+#                 */
/*   Updated: 2023/03/03 22:01:46 by ahorling      ########   odam.nl         */
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
	else if (!info->infilefd)
		info->infilefd = STDIN_FILENO;
	if (commands->outfile)
	{
		info->outfilefd = open(commands->outfile->name, commands->outfile->mode);
		if (dup2(info->outfilefd, STDOUT_FILENO) == -1)
			dupe_error();
		close(info->outfilefd);
	}
	else if (!info->outfilefd)
		info->outfilefd = STDOUT_FILENO;
	if (commands->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			dupe_error();
	}
	close(pipefd[1]);
	close(pipefd[0]);
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
		execute_child(commands, info);
	}
	if (commands->next && !commands->next->infile)
	{
		printf("new command found, no infile found, setting infile to pipe read end\n");
		info->infilefd = pipefd[0];
	}
	else
		printf("no new command found, printing to STD_OUT\n");
	close(pipefd[0]);
	close(pipefd[1]);
	return (pid);
}

void executer(t_commands *commands, char **envp)
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
		if (info->infilefd > 2)
			close(info->infilefd);
		if (info->outfilefd > 2)
			close(info->outfilefd);
	//wait until the last child has finished doing it's stuff
	waitpid(info->lastpid, NULL, 0);
	return ;
}