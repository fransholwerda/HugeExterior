/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 14:38:57 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/03/24 13:43:48 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expand_utils.h"
#include "ft_strlen.h"
#include "ft_substr.h"
#include "ft_is_al_under.h"
#include "stop.h"

static int	expand_dollar(char *env[], char *split[], int i, int pos)
{
	int		end;
	char	*var;
	char	*temp;

	end = expand_dollar_length(split[i], pos);
	var = get_env_var(env, ft_substr(split[i], pos + 1, end - pos));
	temp = split[i];
	split[i] = combine_three_strings(split[i], pos, end + 1, var);
	free(temp);
	free (var);
	return (pos);
}

static void	expand_cmd(char *env[], char *split[], int i)
{
	int	d_quote;
	int	pos;

	d_quote = 0;
	pos = 0;
	while (split[i][pos] != '\0')
	{
		if (split[i][pos] == '\"')
			d_quote = !d_quote;
		if (split[i][pos] == '\'' && d_quote == 0)
		{
			pos++;
			while (split[i][pos] != '\'')
				pos++;
		}
		while (split[i][pos] == '$' && split[i][pos + 1] != ' '
			&& split[i][pos + 1] != '$' && split[i][pos + 1] != '\0')
			pos = expand_dollar(env, split, i, pos);
		pos++;
	}
}

void	expand_split(char *env[], char *split[])
{
	int	i;

	i = 0;
	while (split[i])
	{
		expand_cmd(env, split, i);
		i++;
	}
}
