/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 19:51:30 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/24 13:36:51 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "commandize.h"
#include "cmds_struct_utils.h"
#include "executer.h"
#include "expand.h"
#include "free_split.h"
#include "ft_itoa.h"
#include "ft_strjoin.h"
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

// static void	print_split(char *split[])
// {
// 	int i = 0;
// 	while (split[i])
// 	{
// 		printf("::%s::\n",split[i]);
// 		i++;
// 	}
// 	printf("Next should be NULL:\n");
// 	printf("::%s::\n",split[i]);
// }

static void	unlink_heredocs(t_commands *cmds)
{
	char	*pipe_string;
	char	*filename;
	int		pipe_number;

	pipe_number = 0;
	while (cmds)
	{
		pipe_string = ft_itoa(pipe_number);
		filename = ft_strjoin(".heredoc", pipe_string);
		unlink(filename);
		free(pipe_string);
		pipe_string = NULL;
		free(filename);
		filename = NULL;
		cmds = cmds->next;
		pipe_number++;
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
		if (commandize(info, split))
		{
			trim_cmds(info->cmds);
			redirect_signal(3);
			info->env = executer(info->cmds, info->env);
			redirect_signal(1);
		}
		if (info->cmds)
		{
			unlink_heredocs(info->cmds);
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
