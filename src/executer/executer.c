/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 19:23:48 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/23 22:17:27 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "builtins.h"
#include "errors.h"
#include "exec_utils.h"
#include "extra_utils.h"
#include "ft_strncmp.h"
#include "ft_strrchr.h"
#include "ft_strlen.h"
#include "pathfind.h"
#include "signal.h"
#include "termine.h"
#include "stop.h"
#include "structs.h"
#include "termine.h"

extern int	g_error;

static void	execute_child(t_commands *commands, t_metainfo *info)
{
	if (check_builtin(commands) == true)
		execute_builtin(commands, info);
	if (!commands->args)
		exit(0);
	else if (access(commands->args[0], F_OK) == 0 && ft_strrchr(commands->args[0], '/'))
	{
		if (access(commands->args[0], X_OK) != 0 \
			&& (ft_strncmp(commands->args[0], "./", 2) == 0 \
			|| ft_strncmp(commands->args[0], "../", 3) == 0))
		{
			write(2, "minishell: ", 12);
			write(2, commands->args[0], ft_strlen(commands->args[0]));
			write(2, ": Permission denied\n", 21);
			exit(126);
		}
		info->path = commands->args[0];
		commands->args[0] = ft_strrchr(commands->args[0], '/') + 1;
		execve(info->path, commands->args, info->envp);
		path_error(commands);
	}
	else
	{
		execve(info->path, commands->args, info->envp);
		path_error(commands);
	}
}

static void	child_redirects(t_commands *commands, t_metainfo *info
	, int pipe1[2], int pipe2[2])
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

int	begin_fork(t_commands *commands, t_metainfo *info
	, int pipe1[2], int pipe2[2])
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

t_metainfo	*init_metainfo(char *envp[])
{
	t_metainfo	*info;

	info = malloc(sizeof(t_metainfo));
	if (!info)
		malloc_stop("malloc_executer");
	info->envp = envp;
	info->path = NULL;
	return (info);
}

char	**executer(t_commands *commands, char **envp)
{
	t_metainfo	*info;
	int			pipe1[2];
	int			pipe2[2];
	static int	status = 0;
	char		**envret;

	info = init_metainfo(envp);
	envret = info->envp;
	if (commands && commands->next == NULL)
	{
		if (check_builtin(commands) == true)
		{
			envret = exec_single_builtin(commands, info);
			return (envret);
		}
		else
			exec_single_command(commands, info, pipe1, pipe2);
		waitpid(info->lastpid, &status, 0);
	}
	else
		exec_multiple_commands(commands, info, pipe1, pipe2);
	g_error = get_exit_code(info, status);
	free(info);
	return (envret);
}
