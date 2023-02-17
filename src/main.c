/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 14:50:15 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/17 15:49:05 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "printer.h"
#include "structs.h"
#include "info.h"

#include "split_commands.h"
#include "expand.h"
#include "trim_cmds.h"
#include "separate_cmds.h"
#include "cmds_struct_tools.h"

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

static int	is_data(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (0);
	return (1);
}

int	get_command(t_commands *cmds, char **split, int i)
{
	while (split[i] != NULL && split[i][0] != '|')
	{
		//heredoc <<
		if (split[i][0] == '<' && is_data(split[i + 1]))
			add_infile(cmds, split[i + 1]);
		//append >>
		else if (split[i][0] == '>' && is_data(split[i + 1]))
			add_outfile(cmds, split[i + 1]);
		else
			add_args(cmds, split[i]);
		i++;
	}
	return (i);
}

t_commands	*commandize(t_info *info, char **split)
{
	int			i;

	i = 0;
	if (split[0] && split[0][0] == '|')
	{
		syntax(info->prompt, split[0]);
		return (NULL);
	}
	info->cmds = new_cmds();
	while (split[i])
	{
		if (split[i][0] == '|')
		{
			last_cmd(info->cmds)->next = new_cmds();
			i++;
			if (split[i] == NULL || split[i][0] == '|')
			{
				syntax(info->prompt, split[i]);
				return (NULL);
			}
		}
		i = get_command(last_cmd(info->cmds), split, i);
	}
	return (info->cmds);
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
				printf("Sending stuff to Alex!\n"); //Send stuff to Alex
		}
		//Rework this ^
		free(str);
		str = readline(info->prompt);
	}
	free_info(info);
	free(str);
	return (EXIT_SUCCESS);
}
