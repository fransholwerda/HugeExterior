/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 15:14:30 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/01 18:43:39 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "enums.h"
#include "ft_is_al_under.h"
#include "ft_strjoin.h"
#include "ft_strdup.h"
#include "ft_strlen.h"
#include "ft_strncmp.h"
#include "ft_substr.h"
#include "join_three.h"

int	expand_dollar_length(char *str, int end)
{
	if (ft_is_al_under(str[end + 1]) == True)
	{
		end++;
		while (ft_is_al_under_num(str[end + 1]) == True)
			end++;
	}
	return (end);
}

char	*combine_three_strings(char *str, int start, int end, char *var)
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

char	*get_env_var(char *env[], char *var)
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
