/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 21:15:18 by ahorling      #+#    #+#                 */
/*   Updated: 2023/01/13 20:54:31 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtins.h"
#include "includes/structs.h"

//a function to check which built in, if any, is being called. if none are recognized returns an error.
bool	check_builtins(t_commands commands)
{
	if (ft_strcmp(commands.list_of_commands[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(commands.list_of_commands[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(commands.list_of_commands[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(commands.list_of_commands[0], "export") == 0)
		return (true);
	else if (ft_strcmp(commands.list_of_commands[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(commands.list_of_commands[0], "env") == 0)
		return (true);
	else if (ft_strcmp(commands.list_of_commands[0], "exit") == 0)
		return (true);
	else
		return (false);
}

//currently placeholder checks to confirm what command is being called
int		execute_echo(t_commands commands)
{
	printf("command was: echo\n");
	return (0);
}

int		execute_cd(t_commands commands)
{
	printf("command was: cd\n");
	return (0);
}

int		execute_pwd(t_commands commands)
{
	printf("command was: pwd\n");
	return (0);
}

int		execute_export(t_commands commands)
{
	printf("commands was: export\n");
	return (0);
}

int		execute_unset(t_commands commands)
{
	printf("commands was: unset\n");
	return (0);
}

int		execute_env(t_commands commands)
{
	printf("commands was: env\n");
	return (0);
}

int		execute_exit(t_commands commands)
{
	printf("commands was: exit\n");
	return (0);
}