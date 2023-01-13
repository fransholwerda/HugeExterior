/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/18 23:21:28 by ahorling      #+#    #+#                 */
/*   Updated: 2023/01/13 20:44:55 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "includes/structs.h"

void executer(t_commands *commands, char **envp)
{
	bool		path;
	bool		builtin;
	t_metainfo	info;

	//Check to see if there is only 1 command. If only one, and the command is a builtin, the builtin does not fork into a new process.
	//If only one command and it is not a builtin, then fork and continue as normal, but end the executer upon completion of that one command.
	if (commands->next == NULL)
	{
		builtin = check_builtin(commands->list_of_commands[0]);
		if (builtin == true)
			execute_builtin(commands, envp);
		else
			execute_child(commands, envp);
	}
	//While there are still commands left in the struct, continue moving through it creating pipes
	else
		while (commands->next)
		{
			execute_child(commands, envp);
			commands = commands->next;
		}
	return (global_error_status);
}

execute_child(t_commands *commands, char **envp)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (error_pipe());
	
	
}