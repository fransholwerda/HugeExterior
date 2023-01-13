/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/18 23:21:28 by ahorling      #+#    #+#                 */
/*   Updated: 2023/01/13 21:58:07 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "includes/structs.h"

void executer(t_commands *commands, char **envp)
{
	bool		path;
	bool		builtin;
	t_metainfo	*info;
	int			fd[2];

	//Add envp to the metadata struct for future reference
	info->envp = envp;
	if (open(commands->infile.file) < 0)
		file_error();
	//Check to see if there is only 1 command. If only one, and the command is a builtin, the builtin does not fork into a new process.
	//If only one command and it is not a builtin, then fork and continue as normal, but end the executer upon completion of that one command.
	if (commands->next == NULL)
	{
		builtin = check_builtin(commands->list_of_commands[0]);
		if (builtin == true)
			execute_builtin(commands, envp, fd);
		else
			execute_fork(commands, envp, fd);
	}
	//While there are still commands left in the struct, continue moving through it creating child processes
	else
		while (commands->next)
		{
			execute_fork(commands, envp, fd);
			commands = commands->next;
		}
	waitpid(info->lastpid, 0, NULL);
	return (global_error_status);
}

void	execute_fork(t_commands *commands, t_metainfo *info, int fd[2])
{
	pid_t	pid;

	//check to make sure the pipe opens correctly
	if (pipe(fd) == -1)
		return (error_pipe());
	//fork the process to spawn a child process, and set the lastpid pid to the new child. in a loop the final process will be the final child's pid
	pid = fork();
	info->lastpid = pid;
	//check to see that fork went right
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		fork_error();
	}
	//if child process, execute child process code.
	else if (pid == 0)
		execute_child(commands, info, fd);		
}

void	execute_child(t_commands *commands, t_metainfo *info, int fd[2])
{
	int infile;

	infile = open(commands->infile->file);
	if (infile < 0)
		file_error();
	if (dup2(infile, STDIN_FILENO) < 0)
		dupe_error();
	if (close(infile) < 0)
		close_error();
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		dupe_error();
	if (close(fd[0]) < 0)
		close_error();
	
	
}