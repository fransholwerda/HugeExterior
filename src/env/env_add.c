/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_add.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 17:17:42 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/17 13:11:08 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "array_len.h"
#include "ft_strjoin.h"
#include "stop.h"

static char	*join_three(char *str1, char *str2, char *str3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(str1, str2);
	result = ft_strjoin(temp, str3);
	free(temp);
	return (result);
}

char	**env_add(char *env[], char *var, char *value)
{
	char	**new_env;
	char	*new_var;
	int		i;

	new_env = (char **)malloc((array_len(env) + 2) * sizeof(char *));
	if (!new_env)
		malloc_stop("malloc_env_add");
	new_var = join_three(var, "=", value);
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
