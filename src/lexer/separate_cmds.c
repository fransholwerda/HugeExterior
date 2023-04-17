/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   separate_cmds.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 15:27:23 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/17 20:18:18 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_strlen.h"
#include "ft_substr.h"
#include "stop.h"
#include "split_utils.h"

static void	fill_new_split(char **new_split, char **split, int start, int end)
{
	if (end == -1)
	{
		while (split[start] != NULL)
		{
			new_split[start] = split[start];
			start++;
		}
		new_split[start] = split[start];
	}
	else
	{
		while (start < end)
		{
			new_split[start] = split[start];
			start++;
		}
	}
}

static char	**splinter_new_split(char **split, int i, int start, int end)
{
	char	**new_split;
	int		j;

	if (start == 0 && end == (ft_strlen(split[i])))
		return (split);
	else if (start > 0 && end < (ft_strlen(split[i]) - 1))
		new_split = (char **)malloc((count_split(split) + 3) * sizeof(char *));
	else
		new_split = (char **)malloc((count_split(split) + 2) * sizeof(char *));
	if (!new_split)
		malloc_stop("malloc_splinter_new_split");
	fill_new_split(new_split, split, 0, i);
	j = 0;
	if (start > 0)
	{
		new_split[i] = ft_substr(split[i], 0, start);
		j++;
	}
	if (start == 0 || (start > 0 && j > 0))
	{
		new_split[i + j] = ft_substr(split[i], start, (end - start));
		j++;
	}
	if (end < ft_strlen(split[i]))
	{
		new_split[i + j] = ft_substr(split[i], end, ft_strlen(split[i]));
		j++;
	}
	free(split[i]);
	fill_new_split(&new_split[j - 1], split, i + 1, -1);
	free(split);
	return (new_split);
}

int	skip_until(char *str, int pos, char c)
{
	while (str[pos] != c)
		pos++;
	return (pos);
}

static char	**find_cmds(char **split, int i)
{
	int	len;
	int	pos;

	len = ft_strlen(split[i]);
	pos = 0;
	while (pos < len)
	{
		if (split[i][pos] == '\"')
			pos = skip_until(split[i], pos, '\"');
		else if (split[i][pos] == '\'')
			pos = skip_until(split[i], pos, '\'');
		else if (split[i][pos] == '|')
			split = splinter_new_split(split, i, pos, pos + 1);
		else if (split[i][pos] == '<' && split[i][pos + 1] == '<')
		{
			split = splinter_new_split(split, i, pos, pos + 2);
			pos++;
		}
		else if (split[i][pos] == '<')
			split = splinter_new_split(split, i, pos, pos + 1);
		else if (split[i][pos] == '>' && split[i][pos + 1] == '>')
		{
			split = splinter_new_split(split, i, pos, pos + 2);
			pos++;
		}
		else if (split[i][pos] == '>')
			split = splinter_new_split(split, i, pos, pos + 1);
		pos++;
	}
	return (split);
}

char	**separate_cmds(char **split)
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
