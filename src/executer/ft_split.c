/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 11:53:46 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/09 07:02:14 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static char	**freesplits(char **table, int tableindex)
{
	int	i;

	i = tableindex;
	while (i >= 0)
	{
		free(table[i]);
		i--;
	}
	free(table);
	return (NULL);
}

static int	numofsplits(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	if (i == ft_strlen(s))
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && i != ft_strlen(s) - 1)
			count++;
		i++;
	}
	return (count + 1);
}

static char	*pullstring(char const *s, char c)
{
	int		i;
	int		skip;
	int		length;
	char	*pulledstring;

	i = 0;
	while (s[i] == c)
		i++;
	skip = i;
	while (s[i] != c && s[i] != '\0')
		i++;
	length = i;
	pulledstring = (ft_substr(s, skip, length - skip));
	return (pulledstring);
}

char	**ft_split(char const *s, char c)
{
	int		entries;
	int		i;
	char	**table;

	i = 0;
	if (s == NULL)
		return (NULL);
	entries = numofsplits(s, c);
	table = (char **)malloc((entries + 1) * sizeof(char *));
	if (table == NULL)
		return (NULL);
	while (i < entries)
	{
		table[i] = pullstring(s, c);
		if (table[i] == NULL)
			return (freesplits(table, i));
		while (*s == c)
			s++;
		s = ft_memchr(s, c, ft_strlen(s));
		i++;
	}
	table[i] = NULL;
	return (table);
}
