/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_pop.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 17:41:14 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/01 18:27:17 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "array_len.h"
#include "ft_strjoin.h"
#include "ft_strlen.h"
#include "ft_strncmp.h"
#include "stop.h"

static char	**remove_env_var(char *env[], int env_len, int entry)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)malloc(env_len * sizeof(char *));
	if (!new_env)
		malloc_stop("malloc_remove_env_var");
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != entry)
		{
			new_env[j] = env[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free(env[entry]);
	free(env);
	return (new_env);
}

char	**env_pop(char *env[], char *var)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& (env[i][ft_strlen(var)] == '\0'
			|| env[i][ft_strlen(var)] == '='))
		{
			free(var);
			return (remove_env_var(env, array_len(env), i));
		}
		i++;
	}
	free(var);
	return (env);
}
