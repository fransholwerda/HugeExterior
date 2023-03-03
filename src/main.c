/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 14:50:15 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/03/03 18:27:06 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "structs.h"
#include "info.h"
#include "executer.h"
#include "split_commands.h"
#include "expand.h"
#include "trim_cmds.h"
#include "separate_cmds.h"
#include "commandize.h"

int	g_error = 0;

static int	is_empty(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int	main(int argc, char **argv, char *env[])
{
	//GET ENV INTO OWN ENV, DONT COPY OLD_PWD
	char	*str;
	t_info	*info;
	char	**split;

	if (argc != 1)
		return (EXIT_FAILURE);
	info = init_info(argv, env);
	str = readline(info->prompt);
	while (str != NULL)
	{
		if (!is_empty(str))
			add_history(str);
		//Rework this v
		split = split_commands(str);
		if (split)
		{
			expand_split(env, split);
			split = separate_cmds(split);
			trim_split_cmds(split);
			if (commandize(info, split))
				executer(info->cmds, env);
		}
		//Rework this ^
		free(str);
		str = readline(info->prompt);
	}
	free_info(info);
	free(str);
	return (EXIT_SUCCESS);
}
