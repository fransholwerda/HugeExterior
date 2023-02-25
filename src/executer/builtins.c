/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 21:15:18 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/24 18:59:06 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "unset.h"
#include "builtins.h"
#include "structs.h"
#include "utils.h"


//some are currently placeholder checks to confirm what command is being called
static int		execute_echo(t_commands *commands)
{
	bool	newline;
	int		i;

	i = 0;
	newline = true;
	printf("echo variables set\n");
	if (ft_strncmp(commands->args[1], "-n", 2) != 0)
		newline = false;
	printf("checked for flag, flag is: %d\n", newline);
	if (newline == false)
	{
		printf("preparing to print string\n");
		ft_putstr_fd(commands->args[1], 1);
	}
	else
		ft_putendl_fd(commands->args[2], 1);
	printf("\nstring has been printed\n");
	return (0);
}

static int		execute_cd(t_commands *commands, t_metainfo *info)
{
	(void)commands;
	(void)info;
	printf("command was: cd\n");
	return (0);
}

static int		execute_pwd()
{
	char	*currentdir;

	currentdir = getcwd(NULL, 0);
	ft_putendl_fd(currentdir, 1);
	free(currentdir);
	return (0);
}

static int		execute_export(t_commands *commands, t_metainfo *info)
{
	(void)commands;
	(void)info;
	printf("commands was: export\n");
	return (0);
}

static int		execute_unset(t_commands *commands, t_metainfo *info)
{
	(void)commands;
	(void)info;
	printf("commands was: unset\n");
	unset(info, commands->args[1], 1);
	return (0);
}

static int		execute_env(t_commands *commands, t_metainfo *info)
{
	(void)commands;
	(void)info;
	printf("commands was: env\n");
	return (0);
}

static int		execute_exit(t_commands *commands, t_metainfo *info)
{
	(void)commands;
	(void)info;
	printf("commands was: exit\n");
	return (0);
}

//a function to check which built in, if any, is being called. if none are recognized returns an error.
bool	check_builtin(t_commands *commands)
{
	if (ft_strcmp(commands->args[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(commands->args[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(commands->args[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(commands->args[0], "export") == 0)
		return (true);
	else if (ft_strcmp(commands->args[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(commands->args[0], "env") == 0)
		return (true);
	else if (ft_strcmp(commands->args[0], "exit") == 0)
		return (true);
	else
		return (false);
}

int		execute_builtin(t_commands *commands, t_metainfo *info)
{
	if (ft_strcmp(commands->args[0], "echo") == 0)
	{
		printf("builtin is echo\n");
		return (execute_echo(commands));
	}
	else if (ft_strcmp(commands->args[0], "cd") == 0)
		return (execute_cd(commands, info));
	else if (ft_strcmp(commands->args[0], "pwd") == 0)
		return (execute_pwd());
	else if (ft_strcmp(commands->args[0], "export") == 0)
		return (execute_export(commands, info));
	else if (ft_strcmp(commands->args[0], "unset") == 0)
		return (execute_unset(commands, info));
	else if (ft_strcmp(commands->args[0], "env") == 0)
		return (execute_env(commands, info));
	else if (ft_strcmp(commands->args[0], "exit") == 0)
		return (execute_exit(commands, info));
	else
		return (false);
}


