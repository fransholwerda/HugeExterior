/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 14:50:15 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/16 20:16:45 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "commandize.h"
#include "cmds_struct_tools.h"
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
#include "termine.h"
#include "trim_cmds.h"

int	g_error = 0;

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

void print_split(char **split)
{
	int i = 0;
	while(split[i])
	{
		printf("'%s'\n",split[i]);
		i++;
	}
	printf("\n");
}

int	main(int argc, char **argv, char *env[])
{
	char	*str;
	t_info	*info;
	char	**split;

	if (argc != 1)
		return (EXIT_FAILURE);
	info = init_info(argv, env);
	termion();
	redirect_signal(1);
	str = readline(info->prompt);
	while (true)
	{
		if (!str)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		if (!is_empty(str))
		{
			add_history(str);
			split = split_commands(str);
			if (split)
			{
				expand_split(info->env, split);
				split = separate_cmds(split);
				trim_split_cmds(split);
				if (commandize(info, split))
				{
					//print_split(info->cmds->args);
					//printf("file1: %s, file2: %s\n", info->cmds->infile->name, info->cmds->infile->next->name);
					redirect_signal(3);
					info->env = executer(info->cmds, info->env);
					redirect_signal(1);
				}
				free_split(split);
				free_cmds(info->cmds);
				info->cmds = NULL;
			}
		}
		free(str);
		str = readline(info->prompt);
	}
	free_info(info);
	free(str);
	return (EXIT_SUCCESS);
}

// overloading the forks breaks minishell, pls fix
// fix two heredocs (probably in alex's side of the code)
