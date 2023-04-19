/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_struct_tools.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 16:30:40 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/17 20:09:24 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include "file_struct_tools.h"
#include "array_len.h"
#include "ft_strdup.h"
#include "stop.h"
#include "structs.h"

void	add_infile(t_commands *cmds, char *infile, bool hd)
{
	if (!cmds->infile)
		cmds->infile = new_file(infile, O_RDONLY, -1, hd);
	else
		cmds->infile = file_add_back(cmds->infile,
				new_file(infile, O_RDONLY, -1, hd));
}

void	add_outfile(t_commands *cmds, char *outfile, bool append)
{
	if (!cmds->outfile)
	{
		if (append == true)
			cmds->outfile = new_file(outfile, O_WRONLY | O_APPEND, -1, false);
		else
			cmds->outfile = new_file(outfile, O_CREAT | O_RDWR | O_TRUNC,
					0644, false);
	}
	else
	{
		if (append == true)
			cmds->outfile = file_add_back(cmds->outfile, new_file(outfile,
						O_WRONLY | O_APPEND, -1, false));
		else
			cmds->outfile = file_add_back(cmds->outfile,
					new_file(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644, false));
	}
}

static void	copy_array(char	**to, char **from)
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
