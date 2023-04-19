/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 19:51:30 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/19 17:57:53 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "commandize.h"
#include "cmds_struct_utils.h"
#include "executer.h"
#include "expand.h"
#include "free_split.h"
#include "info.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "separate_cmds.h"
#include "signal.h"
#include "split_commands.h"
#include "structs.h"
#include "trim_cmds.h"

static int	is_empty(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

void print_split(char *split[])
{
	int i = 0;
	//remove
	while (split[i])
	{
		printf("::%s::\n", split[i]);
		i++;
	}
}

void print_cmd(t_commands *cmds)
{
	//remove
	while (cmds && cmds->args)
	{
		print_split(cmds->args);
		cmds = cmds->next;
	}
}

static void	parse_and_execute(t_info *info, char *str)
{
	char	**split;

	add_history(str);
	split = split_commands(str);
	if (split)
	{
		expand_split(info->env, split);
		split = separate_cmds(split);
		trim_split_cmds(split);
		if (commandize(info, split))
		{
			print_cmd(info->cmds);
			redirect_signal(3);
			info->env = executer(info->cmds, info->env);
			redirect_signal(1);
			free_cmds(info->cmds);
			info->cmds = NULL;
		}
		free_split(split);
	}
}

void	minishell(t_info *info)
{
	char	*str;

	str = readline(info->prompt);
	while (true)
	{
		if (!str)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		if (!is_empty(str))
			parse_and_execute(info, str);
		free(str);
		str = readline(info->prompt);
	}
	free(str);
	free_info(info);
}
