/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_struct_tools.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 16:30:40 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/10 17:05:02 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "file_struct_tools.h"
#include "utils.h"
#include "structs.h"






#include <stdio.h>
t_commands	*new_cmds(void)
{
	t_commands	*cmds;

	cmds = (t_commands *)malloc(sizeof(t_commands));
	if (!cmds)
		malloc_stop("malloc_init_cmds");
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
		cmds->infile = new_file(infile, O_RDONLY);
	else
		cmds->infile = file_add_back(cmds->infile, infile, O_RDONLY);
}

void	add_outfile(t_commands *cmds, char *outfile)
{
	if (!cmds->outfile)
		cmds->outfile = new_file(outfile, O_CREAT | O_RDWR | O_TRUNC);
	else
		cmds->outfile = file_add_back(cmds->outfile, outfile,
				O_CREAT | O_RDWR | O_TRUNC);
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	copy_array(char	**to, char **from)
{
	int	i;

	i = 0;
	while (from[i])
	{
		printf("copy_array i: %d\n", i);
		to[i] = from[i];
		i++;
	}
	printf("return copy_array\n");
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
		new_args = malloc((array_len(cmds->args) + 1) * sizeof(char *));
		if (!cmds->args)
			malloc_stop("malloc_add_args_2");
		new_args[array_len(cmds->args) + 1] = NULL;
		copy_array(new_args, cmds->args);
		free_split(cmds->args);
		cmds->args = new_args;
	}
}
