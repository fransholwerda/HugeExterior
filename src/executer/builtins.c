/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 21:15:18 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/12 21:15:45 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "cd.h"
#include "echo.h"
#include "env.h"
#include "exit.h"
#include "export.h"
#include "unset.h"
#include "builtins.h"
#include "structs.h"
#include "utils.h"


//some are currently placeholder checks to confirm what command is being called
static int		execute_echo(t_commands *commands, t_metainfo *info)
{
	(void)info;
	echo(commands, 1);//CHANGE TO info->outfilefd WHEN IT HAS BEEN HANDLED
	return (0);
// 	bool	newline;
// 	int		i;

// 	i = 0;
// 	newline = true;
// 	printf("echo variables set\n");
// 	if (ft_strncmp(commands->args[1], "-n", 2) != 0)
// 		newline = false;
// 	printf("checked for flag, flag is: %d\n", newline);
// 	if (newline == false)
// 	{
// 		printf("preparing to print string\n");
// 		ft_putstr_fd(commands->args[1], 1);
// 	}
// 	else
// 		ft_putendl_fd(commands->args[2], 1);
// 	printf("\nstring has been printed\n");
// 	return (0);
}

static int		execute_cd(t_commands *commands, t_metainfo *info)
{
	cd(commands, info);
	return (0);
}

static int		execute_pwd()
{
	char	*currentdir;

	currentdir = getcwd(NULL, 0);
	ft_putendl_fd(currentdir, 1); //does fd have to be changed?
	free(currentdir);
	return (0);
}

static int		execute_export(t_commands *commands, t_metainfo *info)
{
	info->envp = export(info->envp, commands->args, 1); //change fd
	return (0);
}

static int		execute_unset(t_commands *commands, t_metainfo *info)
{
	(void)commands;
	(void)info;
	printf("commands was: unset\n");
	unset(info, commands->args[1], 1); //change fd
	return (0);
}

static int		execute_env(t_commands *commands, t_metainfo *info)
{
	(void)commands;
	env(info->envp, info->outfilefd);
	return (0);
}

static int		execute_exit(t_commands *commands, t_metainfo *info)
{
	(void)info;
	mini_exit(commands);
	return (0);
}

//a function to check which built in, if any, is being called. if none are recognized returns an error.
bool	check_builtin(t_commands *commands)
{
	if (!commands->args)
		return (false);
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
		return (execute_echo(commands, info));
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
