/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 21:15:18 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/23 16:03:44 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "cd.h"
#include "echo.h"
#include "env.h"
#include "extra_utils.h"
#include "exit.h"
#include "export.h"
#include "pwd.h"
#include "unset.h"
#include "builtins.h"
#include "structs.h"
#include "utils.h"

extern int	g_error;

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

void	execute_builtin(t_commands *commands, t_metainfo *info)
{
	g_error = 0;
	manage_infiles(commands, info);
	manage_outfiles(commands, info);
	if (g_error != 0)
		return ;
	if (ft_strcmp(commands->args[0], "echo") == 0)
		echo(commands, info->outfilefd);
	else if (ft_strcmp(commands->args[0], "cd") == 0)
		cd(commands, info);
	else if (ft_strcmp(commands->args[0], "pwd") == 0)
		pwd(info->outfilefd);
	else if (ft_strcmp(commands->args[0], "export") == 0)
		info->envp = export(info->envp, commands->args, 1);
	else if (ft_strcmp(commands->args[0], "unset") == 0)
		unset(info, commands->args, info->outfilefd);
	else if (ft_strcmp(commands->args[0], "env") == 0)
		env(info->envp, info->outfilefd);
	else if (ft_strcmp(commands->args[0], "exit") == 0)
		mini_exit(commands);
	if (commands->prev || commands->next)
		exit(g_error);
}
