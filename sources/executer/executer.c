/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/18 23:21:28 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/09 06:22:54 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "includes/structs.h"
#include "pathfind.c"
#include "errors.c"
#include "builtins.c"

void executer(t_commands *commands, char **envp)
{
	bool		path;
	bool		builtin;
	t_metainfo	*info;

	//Add envp to the metadata struct for future reference
	info->envp = envp;


	//Check to see if there is only 1 command. If only one, and the command is a builtin, the builtin does not fork into a new process.
	//If only one command and it is not a builtin, then fork and continue as normal, but end the executer upon completion of that one command.
	if (commands->next == NULL)
	{
		builtin = check_builtin(commands->list_of_commands[0]);
		if (builtin == true)
			execute_builtin(commands, info);
		else
			execute_fork(commands, info);
	}
	//While there are still commands left in the struct, continue moving through it creating child processes
	//if the in/outfile fd are greater than the std in/outs, that means they were specified files, and close them
	else
		while (commands->next)
		{
			info->lastpid = execute_fork(commands, info);
			if (info->infilefd > 2)
				close(info->infilefd);
			if (info->outfilefd > 2)
				close(info->outfilefd);
			commands = commands->next;
		}
	//wait until the last child has finished doing it's stuff
	waitpid(info->lastpid, NULL, 0);
	return (global_error);
}

int	execute_fork(t_commands *commands, t_metainfo *info)
{
	pid_t	pid;
	int		pipefd[2];

	//create pipe and check to make sure it is done correctly
	if (pipe(pipefd) == -1)
		return (error_pipe());

	//setting the in and outfile file descriptors to the correct infile/outfile. if none specified default to STDIN/OUT
	if (commands->infile.file != NULL)
		info->infilefd = open(commands->infile.file, commands->infile.mode);
	else
		info->infilefd = STDIN_FILENO;
	if (commands->outfile.file != NULL)
		info->outfilefd = open(commands->outfile.file, commands->outfile.mode);
	else
		info->outfilefd = STDOUT_FILENO;
	
	//fork the process to spawn a child process, and set the lastpid pid to the new child. in a loop the final process will be the final child's pid
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		fork_error();
	}

	//if child process, execute child process code.
	else if (pid == 0)
	{
		execute_child(commands, info, *pipefd);
	}

	//close write end, because all writing to pipe should be done by the child
	close(pipefd[1]);

	//set the read end of the pipe to replace the infilefd of the first file
	if (commands->next != NULL && commands->next->infile.file == NULL)
		commands->next->infile.file = pipefd[0];
	else
		close(pipefd[0]);
	return (pid);
}

void	execute_child(t_commands *commands, t_metainfo *info, int pipefd[2])
{

	//if infile fd links to a given file, redirect STDIN to it and close that fd
	if (info->infilefd != STDIN_FILENO)
	{
		if (dup2(info->infilefd, STDIN_FILENO) == -1)
			dupe_error();
		close(info->infilefd);
	}
	//if outfile fd links to a created file, redirect STDOUT to it and close that fd
	if (info->outfilefd != STDOUT_FILENO)
	{
		if (dup2(info->outfilefd, STDOUT_FILENO) == -1)
			dupe_error();
		close(info->outfilefd);
	}
	//if outfile fd does not link to a new outfile and there is an upcoming command, redirect STDOUT to next process
	else if (commands->next != NULL && dup2(pipefd[1], STDOUT_FILENO == -1))
		dupe_error();
	
	//now that the STDIN/OUT has been redirected, close the hanging write end of the pipe (as all writing now happens on the redirected STDOUT)
	//also close the read end, because all reading should now happen from the STDIN (which is actually a redirected pipefd)
	close(pipefd[1]);
	close(pipefd[0]);

	//check if the command to be executed is a builtin, a command with the path or a command and execute each as neccessary
	if (check_builtin(commands->list_of_commands[0]) == true)
		execute_builtin();
	
	else if (access(commands->list_of_commands[0], F_OK) == 0)
		execve(commands->list_of_commands[0], commands->list_of_commands, info->envp);
	
	else
	{
		info->path = find_path(info, commands);
		execve(path, commands->list_of_commands, info->envp);
	}

	//if the child is still running, then the execve part failed, and the command does not exist
	execute_error();
}