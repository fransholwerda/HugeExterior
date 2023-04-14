/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 21:15:18 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/14 22:18:00 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "cd.h"
#include "echo.h"
#include "env.h"
#include "executer/extra.h"
#include "exit.h"
#include "export.h"
#include "pwd.h"
#include "unset.h"
#include "builtins.h"
#include "structs.h"
#include "utils.h"

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
	manage_infiles(commands, info);
	manage_outfiles(commands, info);
	if (ft_strcmp(commands->args[0], "echo") == 0)
		return (execute_echo(commands, info->outfilefd));
	else if (ft_strcmp(commands->args[0], "cd") == 0)
		return (execute_cd(commands, info));
	else if (ft_strcmp(commands->args[0], "pwd") == 0)
		return (execute_pwd(info->outfilefd));
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
