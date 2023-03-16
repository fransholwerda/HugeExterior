/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 14:38:57 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/03/08 13:37:32 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "enums.h"
#include "ft_strjoin.h"
#include "ft_strdup.h"
#include "ft_strlen.h"
#include "ft_strncmp.h"
#include "ft_substr.h"
#include "ft_is_al_under.h"
#include "stop.h"

static char	*get_env_var(char *env[], char *var)
{
	int		i;
	char	*content;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& env[i][ft_strlen(var)] == '=')
		{
			content = ft_strdup(&env[i][ft_strlen(var) + 1]);
			free(var);
			return (content);
		}
		i++;
	}
	free(var);
	return (ft_strdup(""));
}

static char	*join_three(char *s1, char *s2, char *s3)
{
	char	*new_str;
	char	*temp;

	new_str = ft_strjoin(s1, s2);
	temp = new_str;
	new_str = ft_strjoin(new_str, s3);
	free(temp);
	return (new_str);
}

static char	*combine_three_strings(char *str, int start, int end, char *var)
{
	int		len;
	char	*s1;
	char	*s2;
	char	*new_str;

	len = ft_strlen(str);
	s1 = NULL;
	s2 = NULL;
	if (start > 0)
		s1 = ft_substr(str, 0, start);
	if (end < len)
		s2 = ft_substr(str, end, len);
	if (s1 && s2)
		new_str = join_three(s1, var, s2);
	else if (s1 && !s2)
		new_str = ft_strjoin(s1, var);
	else if (!s1 && s2)
		new_str = ft_strjoin(var, s2);
	else
		new_str = ft_strdup(var);
	free(s1);
	free(s2);
	return (new_str);
}

static int	expand_dollar(char *env[], char *split[], int i, int pos)
{
	int		end;
	char	*var;
	char	*temp;

	end = pos;
	if (ft_is_al_under(split[i][end + 1]) == True)
	{
		end++;
		while (ft_is_al_under_num(split[i][end + 1]) == True)
			end++;
	}
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
