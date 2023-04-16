/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commandize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 13:25:47 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/16 14:23:18 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "cmds_struct_tools.h"
#include "heredoc.h"
#include "printer.h"
#include "structs.h"



#include <stdio.h>
static int	is_data(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (0);
	return (1);
}

static int	get_command(t_info *info, int pipe, char **split, int i)
{
	t_commands	*cmds;
	char		*hd_file;

	cmds = last_cmd(info->cmds);
	while (split[i] != NULL && split[i][0] != '|')
	{
		if (split[i][0] == '<' && split[i][1] == '<'
			&& is_data(split[i + 1]))
		{
			hd_file = go_heredoc(info->env, split[i + 1], pipe);
			if (!hd_file)
				return (-1);
			add_infile(cmds, hd_file, true);
			i++;
		}
		else if (split[i][0] == '<' && is_data(split[i + 1]))
		{
			add_infile(cmds, split[i + 1], false);
			i++;
		}
		else if (split[i][0] == '>' && split[i][1] == '>'
			&& is_data(split[i + 1]))
		{
			add_outfile(cmds, split[i + 1], true);
			i++;
		}
		else if (split[i][0] == '>' && is_data(split[i + 1]))
		{
			add_outfile(cmds, split[i + 1], false);
			i++;
		}
		else
			add_args(cmds, split[i]);
		i++;
	}
	return (i);
}

t_commands	*commandize(t_info *info, char **split)
{
	int	pipe;
	int	i;

	pipe = 0;
	i = 0;
	if (split[0] && split[0][0] == '|')
	{
		syntax(info->prompt, split[0]);
		return (NULL);
	}
	info->cmds = new_cmds(NULL);
	while (split[i])
	{
		if (split[i][0] == '|')
		{
			last_cmd(info->cmds)->next = new_cmds(last_cmd(info->cmds));
			pipe++;
			i++;
			if (split[i] == NULL || split[i][0] == '|')
			{
				syntax(info->prompt, "|");
				return (NULL);
			}
		}
		i = get_command(info, pipe, split, i);
		if (i < 0)
		{
			//check for fork return warning
			return (NULL);
		}
	}
	return (info->cmds);
}

//FIX SYNTAX ERRORS WHEN TWO OPERATORS ARE NEXT TO EACHOTHER
