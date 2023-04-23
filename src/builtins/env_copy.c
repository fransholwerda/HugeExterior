/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_copy.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 17:03:45 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/23 18:16:17 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expand_utils.h"
#include "export.h"
#include "ft_atoi.h"
#include "ft_itoa.h"
#include "ft_strcmp.h"
#include "ft_strdup.h"
#include "ft_strjoin.h"
#include "ft_strncmp.h"
#include "stop.h"
#include "structs.h"

// Will count how many entries there are in env, excluding the OLDPWD entry
// #include <stdio.h>
// #include "array_len.h"
static int	env_len_no_oldpwd(char *env[])
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) != 0)
			count++;
		i++;
	}
	return (count);
}

static char	*get_shlvl(char *env[], int i)
{
	int		equal;
	int		int_value;
	char	*value;
	char	*new_var;

	equal = find_char(env[i], '=');
	value = get_env_var(env, ft_strdup("SHLVL"));
	int_value = ft_atoi(value) + 1;
	free(value);
	value = ft_itoa(int_value);
	new_var = ft_strjoin("SHLVL=", value);
	free(value);
	value = NULL;
	return (new_var);
	return (NULL);
}

static int	find_shlvl_oldpwd(char *env[], char *new_env[], int i, int j)
{
	if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
	{
		new_env[j] = get_shlvl(env, i);
		j++;
	}
	else if (ft_strncmp(env[i], "OLDPWD=", 7) != 0)
	{
		new_env[j] = ft_strdup(env[i]);
		j++;
	}
	return (j);
}

//Will make a copy of env without OLDPWD
char	**env_copy(char *env[])
{
	char	**new_env;
	int		new_env_len;
	int		i;
	int		j;

	new_env_len = env_len_no_oldpwd(env);
	new_env = (char **)malloc((new_env_len + 1) * sizeof(char *));
	new_env[new_env_len] = NULL;
	if (!new_env)
		malloc_stop("malloc_copy_env");
	i = 0;
	j = 0;
	while (env[i])
	{
		j = find_shlvl_oldpwd(env, new_env, i, j);
		i++;
	}
	return (new_env);
}
