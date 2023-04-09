/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 19:23:48 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/09 19:37:20 by ahorling      ########   odam.nl         */
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
	return (global_error());
}

static void	child_redirects(t_commands *commands, t_metainfo *info, int pipe1[2], int pipe2[2])
{
	if (info->infilefd != STDIN_FILENO)
	{
		dup2(info->infilefd, STDIN_FILENO);
		close(info->infilefd);
		if (commands->prev)
		{
			close(pipe1[1]);
			close(pipe1[0]);
		}
	}
	else if (commands->prev)
	{
		dup2(pipe1[0], STDIN_FILENO);
		close(pipe1[1]);
		close(pipe1[0]);
	}
	if (info->outfilefd != STDOUT_FILENO)
	{
		dup2(info->outfilefd, STDOUT_FILENO);
		close(info->outfilefd);
		if (commands->next)
		{
			close(pipe2[1]);
			close(pipe2[0]);
		}
	}
	else if (commands->next)
	{
		close(pipe2[0]);
		dup2(pipe2[1], STDOUT_FILENO);
		close(pipe2[1]);
	}
}

static void	setup_info(t_commands *commands, t_metainfo *info)
{
	info->path = find_path(info, commands);
	if (commands->infile)
	{
		while (commands->infile)
		{
			if (access(commands->infile->name, F_OK) != 0)
			{
				printf("minishell: %s: No suchfile or directory\n", commands->infile->name);
				return(global_error());
			}
			else if (access(commands->infile->name, R_OK) != 0)
			{
				printf("minishell: %s: Permission denied\n", commands->infile->name);
				return(global_error());
			}
			else
				info->infilefd = open(commands->infile->name, commands->infile->mode);
			commands->infile = commands->infile->next;
		}
	}
	else
		info->infilefd = STDIN_FILENO;
	if (commands->outfile)
	{
		while (commands->outfile)
		{
			if (access(commands->outfile->name, F_OK) != 0)
					info->outfilefd = open(commands->outfile->name, O_RDWR|O_CREAT, 0655);
			else if (access(commands->outfile->name, W_OK) == 0)
					info->outfilefd = open(commands->outfile->name, commands->outfile->mode);
			else
			{
				printf("minishell: %s: Permission denied\n", commands->outfile->name);
				return(global_error());
			}
			commands->outfile = commands->outfile->next;
		}
	}
	else
		info->outfilefd = STDOUT_FILENO;
}

static int		begin_fork(t_commands *commands, t_metainfo *info, int pipe1[2], int pipe2[2])
{
	pid_t	pid;

	if (commands->next)
		pipe(pipe2);
	pid = fork();
	if (pid == 0)
	{
		setup_info(commands, info);
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
	return (pid);
}

char	**executer(t_commands *commands, char **envp)
{
	t_metainfo	*info;
	int			pipe1[2];
	int			pipe2[2];

	info = malloc(sizeof(t_metainfo));
	info->envp = envp;
	if (commands && commands->next == NULL)
	{
		if (check_builtin(commands) == true)
			execute_builtin(commands, info);
		else
		{
			info->lastpid = begin_fork(commands, info, pipe1, pipe2);
			waitpid(info->lastpid, NULL, 0);
		}
	}
	else
	{
		while(commands)
		{
			info->lastpid = begin_fork(commands, info, pipe1, pipe2);
			if (commands->next == NULL)
				break;
			commands = commands->next;
		}
	}
	if (commands->prev)
	{
		close(pipe1[0]);
		close(pipe1[1]);
	}
	waitpid(info->lastpid, NULL, 0);
	return (info->envp);
}