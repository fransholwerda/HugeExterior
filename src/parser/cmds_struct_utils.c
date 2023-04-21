/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_struct_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 20:05:10 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/19 17:45:19 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "file_struct_tools.h"
#include "free_split.h"
#include "stop.h"
#include "structs.h"

void	free_cmds(t_commands *cmds)
{
	t_commands	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->args)
			free_split(cmds->args);
		if (cmds->infile)
			free_file(cmds->infile);
		if (cmds->outfile)
			free_file(cmds->outfile);
		free(cmds);
		cmds = NULL;
		cmds = tmp;
	}
}

t_commands	*new_cmds(t_commands *prev)
{
	t_commands	*cmds;

	cmds = (t_commands *)malloc(sizeof(t_commands));
	if (!cmds)
		malloc_stop("malloc_init_cmds");
	cmds->args = NULL;
	cmds->infile = NULL;
	cmds->outfile = NULL;
	cmds->next = NULL;
	cmds->prev = prev;
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
