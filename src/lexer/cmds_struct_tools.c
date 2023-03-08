/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_struct_tools.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 16:30:40 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/26 18:52:19 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include "file_struct_tools.h"
#include "array_len.h"
#include "free_split.h"
#include "ft_strdup.h"
#include "stop.h"
#include "structs.h"



#include <stdio.h>
t_commands	*new_cmds(void)
{
	t_commands	*cmds;

	cmds = (t_commands *)malloc(sizeof(t_commands));
	if (!cmds)
		malloc_stop("malloc_init_cmds");
	cmds->args = NULL;
	cmds->infile = NULL;
	cmds->outfile = NULL;
	cmds->next = NULL;
	return (cmds);
}

t_commands	*last_cmd(t_commands *cmds)
{
	t_commands	*ret_cmd;

	ret_cmd = cmds;
	while (ret_cmd->next)
		ret_cmd = ret_cmd->next;
	return (ret_cmd);
}

void	add_infile(t_commands *cmds, char *infile)
{
	if (!cmds->infile)
		cmds->infile = new_file(infile, O_RDONLY, -1);
	else
		cmds->infile = file_add_back(cmds->infile, infile, O_RDONLY, -1);
}

void	add_outfile(t_commands *cmds, char *outfile, bool append)
{
	if (!cmds->outfile)
	{
		if (append == true)
			cmds->outfile = new_file(outfile, O_WRONLY | O_APPEND, -1);
		else
			cmds->outfile = new_file(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else
	{
		if (append == true)
			cmds->outfile = file_add_back(cmds->outfile, outfile,
					O_WRONLY | O_APPEND, -1);
		else
			cmds->outfile = file_add_back(cmds->outfile, outfile,
					O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
}

void	copy_array(char	**to, char **from)
{
	int	i;

	i = 0;
	while (from[i])
	{
		to[i] = from[i];
		i++;
	}
}

void	add_args(t_commands *cmds, char *arg)
{
	char	**new_args;

	if (!cmds->args)
	{
		cmds->args = (char **)malloc(2 * sizeof(char *));
		if (!cmds->args)
			malloc_stop("malloc_add_args_1");
		cmds->args[0] = ft_strdup(arg);
		cmds->args[1] = NULL;
	}
	else
	{
		new_args = malloc((array_len(cmds->args) + 2) * sizeof(char *));
		if (!cmds->args)
			malloc_stop("malloc_add_args_2");
		new_args[array_len(cmds->args) + 1] = NULL;
		new_args[array_len(cmds->args)] = ft_strdup(arg);
		copy_array(new_args, cmds->args);
		free(cmds->args);
		cmds->args = new_args;
	}
}
