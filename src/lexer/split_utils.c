/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 13:00:15 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/06 17:58:31 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

static int	skip_single_quote(char *str, int pos)
{
	pos++;
	while (str[pos] != '\'')
	{
		if (str[pos] == '\0')
		{
			write(2, "Could not find a closing quote.\n", 32);
			return (-1);
		}
		pos++;
	}
	return (pos);
}

static int	skip_double_quote(char *str, int pos)
{
	pos++;
	while (str[pos] != '\"')
	{
		if (str[pos] == '\0')
		{
			write(2, "Could not find a closing quote.\n", 32);
			return (-1);
		}
		pos++;
	}
	return (pos);
}

int	skip(char *str, int pos)
// pos++;
// while (str[pos] != '\'')
// {
// 	if (str[pos] == '\0')
// 	{
// 		write(2, "Could not find a closing quote.\n", 32);
// 		return (-1);
// 	}
// 	pos++;
// }

// pos++;
// while (str[pos] != '\"')
// {
// 	if (str[pos] == '\0')
// 	{
// 		write(2, "Could not find a closing quote.\n", 32);
// 		return (-1);
// 	}
// 	pos++;
// }
{
	while (str[pos])
	{
		if (str[pos] == '\'')
			pos = skip_single_quote(str, pos);
		else if (str[pos] == '\"')
			pos = skip_double_quote(str, pos);
		else if (str[pos] == ' ')
			return (pos);
		if (pos == -1)
			return (-1);
		pos++;
	}
	return (pos);
}
