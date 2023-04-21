/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splinter_split.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 14:57:56 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/20 21:17:46 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_strlen.h"
#include "ft_substr.h"
#include "split_utils.h"
#include "stop.h"
#include "structs.h"

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

static int	splinter(t_three_ints ints, char *new_split[], char *split[])
{
	int	j;

	j = 0;
	if (ints.start > 0)
	{
		new_split[ints.i] = ft_substr(split[ints.i], 0, ints.start);
		j++;
	}
	if (ints.start == 0 || (ints.start > 0 && j > 0))
	{
		new_split[ints.i + j]
			= ft_substr(split[ints.i], ints.start, (ints.end - ints.start));
		j++;
	}
	if (ints.end < ft_strlen(split[ints.i]))
	{
		new_split[ints.i + j]
			= ft_substr(split[ints.i], ints.end, ft_strlen(split[ints.i]));
		j++;
	}
	return (j);
}

//else if (start > 0 && end < (ft_strlen(split[i]) - 1)) #83
char	**splinter_new_split(char **split, int i, int start, int end)
{
	t_three_ints	ints;
	char			**new_split;
	int				j;

	ints.start = start;
	ints.end = end;
	ints.i = i;
	if (start == 0 && end == (ft_strlen(split[i])))
		return (split);
	else if (start > 0 && end < (ft_strlen(split[i])))
		new_split = (char **)malloc((count_split(split) + 3) * sizeof(char *));
	else
		new_split = (char **)malloc((count_split(split) + 2) * sizeof(char *));
	if (!new_split)
		malloc_stop("malloc_splinter_new_split");
	fill_new_split(new_split, split, 0, i);
	j = splinter(ints, new_split, split);
	free(split[i]);
	fill_new_split(&new_split[j - 1], split, i + 1, -1);
	free(split);
	split = NULL;
	return (new_split);
}
