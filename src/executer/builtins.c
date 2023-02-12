/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 21:15:18 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/12 22:28:39 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer/builtins.h"
#include "structs.h"
#include "utils.h"
#include <stdbool.h>
#include <unistd.h>

//a function to check which built in, if any, is being called. if none are recognized returns an error.
bool	check_builtins(t_commands *commands)
{
	if (ft_strcmp(commands->list_of_commands[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(commands->list_of_commands[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(commands->list_of_commands[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(commands->list_of_commands[0], "export") == 0)
		return (true);
	else if (ft_strcmp(commands->list_of_commands[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(commands->list_of_commands[0], "env") == 0)
		return (true);
	else if (ft_strcmp(commands->list_of_commands[0], "exit") == 0)
		return (true);
	else
		return (false);
}

int		execute_builtins(t_commands *commands, t_metainfo *info)
{
	if (ft_strcmp(commands->list_of_commands[0], "echo") == 0)
		return (execute_echo(commands, info));
	else if (ft_strcmp(commands->list_of_commands[0], "cd") == 0)
		return (execute_echo(commands, info));
	else if (ft_strcmp(commands->list_of_commands[0], "pwd") == 0)
		return (execute_echo(commands, info));
	else if (ft_strcmp(commands->list_of_commands[0], "export") == 0)
		return (execute_echo(commands, info));
	else if (ft_strcmp(commands->list_of_commands[0], "unset") == 0)
		return (execute_echo(commands, info));
	else if (ft_strcmp(commands->list_of_commands[0], "env") == 0)
		return (execute_echo(commands, info));
	else if (ft_strcmp(commands->list_of_commands[0], "exit") == 0)
		return (execute_echo(commands, info));
	else
		return (false);
}



//some are currently placeholder checks to confirm what command is being called
int		execute_echo(t_commands *commands, t_metainfo *info)
{
	bool	newline;
	int		i;

	i = 0;
	newline = true;
	if (ft_strcmp(commands->list_of_commands[1], "-n", 2) == 0)
		newline = false;
	ft_putstr_fd(commands->list_of_commands[2], 1);
	if (newline = true)
		write(1, "\n", 1);
	return (0);
}

int		execute_cd(t_commands commands, t_metainfo *info)
{
	printf("command was: cd\n");
	return (0);
}

int		execute_pwd(t_commands commands, t_metainfo *info)
{
	char	*currentdir;

	currentdir = getcwd(NULL, 0);
	ft_putendl_fd(currentdir, 1);
	free(currentdir);
	return (0);
}

int		execute_export(t_commands commands, t_metainfo *info)
{
	printf("commands was: export\n");
	return (0);
}

int		execute_unset(t_commands commands, t_metainfo *info)
{
	printf("commands was: unset\n");
	return (0);
}

int		execute_env(t_commands commands, t_metainfo *info)
{
	printf("commands was: env\n");
	return (0);
}

int		execute_exit(t_commands commands, t_metainfo *info)
{
	printf("commands was: exit\n");
	return (0);
}