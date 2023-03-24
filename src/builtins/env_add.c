/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_add.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 17:17:42 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/03/22 14:55:02 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "array_len.h"
#include "ft_strdup.h"
#include "ft_strjoin.h"
#include "ft_strlen.h"
#include "ft_strncmp.h"
#include "stop.h"

extern int	g_error;

static char	*join_four(char *str1, char *str2, char *str3, char *str4)
{
	char	*temp1;
	char	*temp2;
	char	*result;

	temp1 = ft_strjoin(str1, str2);
	temp2 = ft_strjoin(str3, str4);
	result = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	return (result);
}

int	env_find_var(char *env[], char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& env[i][ft_strlen(var)] == '=')
			return (i);
	}
	return (-1);
}

char	**env_add(char *env[], char *var, char *value)
{
	char	**new_env;
	char	*new_var;
	int		i;

	new_env = (char **)malloc((array_len(env) + 2) * sizeof(char *));
	if (!new_env)
		malloc_stop("malloc_env_add");
	if (value)
		new_var = join_four(var, "=\"", value, "\"");
	else
		new_var = ft_strdup(var);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}
