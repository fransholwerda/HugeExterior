/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 12:56:01 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/06 18:03:57 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "split_utils.h"
#include "utils.h"
#include <stdlib.h>

static int	count_commands(char *str)
{
	int	count;
	int	strlen;
	int	pos;

	count = 0;
	strlen = ft_strlen(str);
	pos = 0;
	while (pos < strlen)
	{
		if (str[pos] != ' ' && str[pos] != '\t' && str[pos] != '\n')
		{
			count++;
			pos = skip(str, pos);
			if (pos == -1)
				return (-1);
		}
		else
			pos++;
	}
	return (count);
}

static char	*fill_word(char *str)
{
	int		word_len;
	int		pos;
	char	*word;

	word_len = skip(str, 0);
	pos = 0;
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!word)
		malloc_stop("malloc_fill_word");
	word[word_len] = '\0';
	while (pos < word_len)
	{
		word[pos] = str[pos];
		pos++;
	}
	return (word);
}

static void	fill_split(char *str, char *split[], int cmd_amount)
{
	int	i;
	int	strlen;
	int	pos;

	i = 0;
	strlen = ft_strlen(str);
	pos = 0;
	while (pos < strlen && i < cmd_amount)
	{
		if (str[pos] != ' ' && str[pos] != '\t' && str[pos] != '\n')
		{
			split[i] = fill_word(&str[pos]);
			pos = skip(str, pos);
			i++;
		}
		pos++;
	}
}

char	**split_commands(char *str)
{
	char	**split;
	int		cmd_amount;

	cmd_amount = count_commands(str);
	if (cmd_amount == -1)
		return (NULL);
	split = (char **)malloc((cmd_amount + 1) * sizeof(char *));
	if (!split)
		malloc_stop("malloc_split_commands");
	split[cmd_amount] = NULL;
	fill_split(str, split, cmd_amount);
	return (split);
}
