/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 19:49:03 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/17 13:21:12 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "free_split.h"
#include "ft_strlen.h"
#include "stop.h"

static int	word_count(const char *s, char c)
{
	int	count;
	int	i;

	if (ft_strlen(s) == 0)
		return (0);
	if (s[0] && !s[1])
		return (1);
	count = 0;
	i = 1;
	while (s[i])
	{
		if ((s[i] != c && s[i - 1] == c) || (i == 1 && s[0] != c))
			count++;
		i++;
	}
	return (count);
}

static char	*add_word(const char *s, char c, int i)
{
	unsigned int	count;
	unsigned int	j;
	char			*word;

	count = 0;
	while (s[i + count] != c && s[i + count])
		count++;
	word = malloc((count + 1) * sizeof(char));
	if (!word)
		malloc_stop("malloc_ft_split_add_word");
	j = 0;
	while (j < count)
	{
		word[j] = s[i];
		i++;
		j++;
	}
	word[count] = '\0';
	return (word);
}

static char	**fill_result(char **result, const char *s, char c)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			result[j] = add_word(s, c, i);
			if (!result[j])
			{
				free_split(result);
				return (NULL);
			}
			j++;
			while (s[i] != c && s[i])
				i++;
		}
		if (s[i])
			i++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(const char *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!result)
		malloc_stop("malloc_ft_split");
	result[word_count(s, c)] = NULL;
	result = fill_result(result, s, c);
	if (!result)
		return (NULL);
	return (result);
}
