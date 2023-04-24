/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commandize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 13:25:47 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/24 15:47:26 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "cmds_struct_tools.h"
#include "cmds_struct_utils.h"
#include "heredoc.h"
#include "printer.h"
#include "structs.h"
#include "trim_cmds.h"

static int	is_data(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (0);
	return (1);
}

static int	add_heredoc(t_info *info, char *data, int pipe)
{
	char	*hd_file;

	if (is_data(data))
	{
		hd_file = go_heredoc(info->env, data, pipe);
		if (!hd_file)
			return (-1);
		add_infile(last_cmd(info->cmds), hd_file, true);
	}
	else
	{
		syntax(info->prompt, data);
		return (-1);
	}
	return (1);
}

static int	add_file(t_info *info, char *data,
	void (*f)(t_commands *, char *, bool), bool hd_app)
{
	t_commands	*cmds;

	cmds = last_cmd(info->cmds);
	if (is_data(data))
		f(cmds, data, hd_app);
	else
	{
		syntax(info->prompt, data);
		return (-1);
	}
	return (1);
}

static int	get_command(t_info *info, int pipe, char **split, int i)
{
	int	original_i;

	while (split[i] != NULL && split[i][0] != '|')
	{
		original_i = i;
		if (split[i][0] == '<' && split[i][1] == '<')
			i += add_heredoc(info, trim_split_cmds(split, i + 1), pipe);
		else if (split[i][0] == '<')
			i += add_file(info, trim_split_cmds(split, i + 1),
					&add_infile, false);
		else if (split[i][0] == '>' && split[i][1] == '>')
			i += add_file(info, trim_split_cmds(split, i + 1),
					&add_outfile, true);
		else if (split[i][0] == '>')
			i += add_file(info, trim_split_cmds(split, i + 1),
					&add_outfile, false);
		else
			add_args(last_cmd(info->cmds), split[i]);
		if (original_i > i)
			return (-1);
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
		return (syntax(info->prompt, split[0]));
	info->cmds = new_cmds(NULL);
	while (split[i])
	{
		if (split[i][0] == '|')
		{
			last_cmd(info->cmds)->next = new_cmds(last_cmd(info->cmds));
			pipe++;
			i++;
			if (split[i] == NULL || split[i][0] == '|')
				return (syntax(info->prompt, "|"));
		}
		i = get_command(info, pipe, split, i);
		if (i < 0)
			return (NULL);
	}
	return (info->cmds);
}
