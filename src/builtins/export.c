/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 17:39:10 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/02 16:43:34 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "array_len.h"
#include "array_sort.h"
#include "enums.h"
#include "env_add.h"
#include "env_pop.h"
#include "export_utils.h"
#include "ft_strdup.h"
#include "ft_strlen.h"
#include "ft_strndup.h"
#include "is_valid_varname.h"



#include <stdio.h>
extern int	g_error;

static void	print_export(char *env[], int fd)
{
	int	i;

	array_sort(env);
	i = 0;
	while (env[i])
	{
		write(fd, "declare -x ", 11);
		write(fd, env[i], ft_strlen(env[i]));
		write(fd, "\n", 1);
		i++;
	}
}

static int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char	**export_var(char *env[], char *var)
{
	int		equal_pos;
	int		var_pos;

	equal_pos = find_char(var, '=');
	var_pos = env_find_var(env, var);
	if (equal_pos == -1 && var_pos == -1)
		env = env_add(env, var, NULL);
	else if (equal_pos > -1 && var_pos > -1)
	{
		env = env_pop(env, ft_strndup(var, equal_pos));
		env = env_add(env, ft_strndup(var, equal_pos),
				ft_strdup(&var[equal_pos + 1]));
	}
	else
	{
		env = env_add(env, ft_strndup(var, equal_pos),
				ft_strdup(&var[equal_pos + 1]));
	}
	return (env);
}

char	**export(char *env[], char *args[], int fd)
{
	int		i;

	g_error = 0;
	//validate args
	if (array_len(args) == 1)
	{
		print_export(env, fd);
		return (env);
	}
	i = 1;
	while (args[i] != NULL)
	{
		// if (export_validate(args[i]) == True)
		env = export_var(env, args[i]);
		i++;
	}
	printf("g_error: %d\n", g_error);
	return (env);
}
