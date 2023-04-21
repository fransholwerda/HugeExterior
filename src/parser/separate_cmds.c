/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   separate_cmds.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 15:27:23 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/21 12:53:20 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_strlen.h"
#include "ft_substr.h"
#include "splinter_split.h"
#include "split_utils.h"
#include "stop.h"
#include "structs.h"

int	skip_until(char *str, int pos, char c)
{
	while (str[pos] && str[pos] != c)
		pos++;
	return (pos);
}

static char	**check_operators(char *split[], int i, int *pos)
{
	if (split[i][*pos] && split[i][*pos] == '\"')
		*pos = skip_until(split[i], *pos + 1, '\"');
	else if (split[i][*pos] == '\'')
		*pos = skip_until(split[i], *pos + 1, '\'');
	else if (split[i][*pos] == '|')
		split = splinter_new_split(split, i, *pos, *pos + 1);
	else if (split[i][*pos] == '<' && split[i][*pos + 1] == '<')
	{
		split = splinter_new_split(split, i, *pos, *pos + 2);
		*pos += 1;
	}
	else if (split[i][*pos] == '<')
		split = splinter_new_split(split, i, *pos, *pos + 1);
	else if (split[i][*pos] == '>' && split[i][*pos + 1] == '>')
	{
		split = splinter_new_split(split, i, *pos, *pos + 2);
		*pos += 1;
	}
	else if (split[i][*pos] == '>')
		split = splinter_new_split(split, i, *pos, *pos + 1);
	*pos += 1;
	return (split);
}

static char	**find_cmds(char *split[], int i)
{
	int	len;
	int	pos;

	len = ft_strlen(split[i]);
	pos = 0;
	while (pos < len)
	{
		split = check_operators(split, i, &pos);
		len = ft_strlen(split[i]);
	}
	return (split);
}

char	**separate_cmds(char *split[])
{
	int	i;

	i = 0;
	while (split[i])
	{
		split = find_cmds(split, i);
		i++;
	}
	return (split);
}
