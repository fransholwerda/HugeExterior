/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_add.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 17:17:42 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/19 17:46:56 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "array_len.h"
#include "ft_strdup.h"
#include "ft_strjoin.h"
#include "ft_strlen.h"
#include "ft_strncmp.h"
#include "join_three.h"
#include "stop.h"





#include <stdio.h>
extern int	g_error;

int	env_find_var(char *env[], char *var)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '\0' && env[i][j] != '='
			&& var[j] != '=' && env[i][j] == var[j])
			j++;
		if ((var[j] == '\0' || var[j] == '=')
			&& (env[i][j] == '\0' || env[i][j] == '='))
			return (i);
		// if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
		// 	return (i);
		i++;
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
		new_var = join_three(var, "=", value);
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
	free(var);
	free(value);
	free(env);
	return (new_env);
}
