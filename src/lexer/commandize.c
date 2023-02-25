/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commandize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 13:25:47 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/25 17:44:43 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds_struct_tools.h"
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

static int	get_command(t_commands *cmds, char **split, int i)
{
	while (split[i] != NULL && split[i][0] != '|')
	{
		//heredoc <<
		if (split[i][0] == '<' && is_data(split[i + 1]))
		{
			add_infile(cmds, split[i + 1]);
			i++;
		}
		//append >>
		else if (split[i][0] == '>' && is_data(split[i + 1]))
		{
			add_outfile(cmds, split[i + 1]);
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
	int	i;

	i = 0;
	if (split[0] && split[0][0] == '|')
	{
		syntax(info->prompt, split[0]);
		return (NULL);
	}
	info->cmds = new_cmds();
	//printf("COMMANDIZE LOOP START\n");
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
		// int j = 0;
		// while (info->cmds->args[j])
		// {
		// 	printf("%s, ", info->cmds->args[j]);
		// 	j++;
		// }
		// printf("\n");
	}
	return (info->cmds);
}
