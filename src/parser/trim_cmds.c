/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trim_cmds.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 15:25:02 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/21 12:43:12 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "separate_cmds.h"
#include "stop.h"
#include <stdlib.h>

static void	trim_cmd(char **split, int i, int q1, int q2)
{
	char	*new_str;
	int		len;
	int		pos;
	int		skip;

	len = ft_strlen(split[i]) - 2;
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		malloc_stop("malloc_trim_cmd");
	pos = 0;
	skip = 0;
	while (pos < len)
	{
		if (pos == q1)
			skip++;
		if (pos == q2)
			skip++;
		new_str[pos] = split[i][pos + skip];
		pos++;
	}
	new_str[pos] = '\0';
	free(split[i]);
	split[i] = new_str;
}

static void	find_trim(char **split, int i)
{
	int	pos;
	int	q1;
	int	q2;

	pos = 0;
	while (split[i][pos])
	{
		if (split[i][pos] == '\'')
		{
			q1 = pos;
			pos = skip_until(split[i], pos + 1, '\'');
			q2 = pos - 1;
			trim_cmd(split, i, q1, q2);
			pos -= 2;
		}
		else if (split[i][pos] == '\"')
		{
			q1 = pos;
			pos = skip_until(split[i], pos + 1, '\"');
			q2 = pos - 1;
			trim_cmd(split, i, q1, q2);
			pos -= 2;
		}
		pos++;
	}
}

void	trim_split_cmds(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		find_trim(split, i);
		i++;
	}
}

void	trim_cmds(t_commands *cmds)
{
	while (cmds)
	{
		trim_split_cmds(cmds->args);
		cmds = cmds->next;
	}
}
