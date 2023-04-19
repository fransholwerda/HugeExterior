/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_copy.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 17:03:45 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/19 17:22:58 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs.h"
#include "ft_strdup.h"
#include "ft_strncmp.h"
#include "stop.h"

//Will count how many entries there are in env, excluding the OLDPWD entry
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
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			count--;
		i++;
	}
	count++;
	return (count);
}

// static int	get_shlvl(char *env[], int j)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], "SHLVL=", 6) )
// 			return (replace_shlvl());
// 	}
// 	return (create_shlvl());
// }

//Will make a copy of env without OLDPWD
char	**env_copy(char *env[])
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)malloc((env_len_no_oldpwd(env) + 1) * sizeof(char *));
	if (!new_env)
		malloc_stop("malloc_copy_env");
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) != 0)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	//j = get_shlvl(new_env, j);
	new_env[j] = NULL;
	return (new_env);
}
