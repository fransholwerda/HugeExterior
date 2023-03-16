/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 17:39:10 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/03/08 17:21:36 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "array_len.h"
#include "array_sort.h"
#include "env_add.h"
#include "ft_strdup.h"
#include "ft_strlen.h"
#include "ft_strndup.h"
#include "is_valid_varname.h"

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
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static void	export_var(char *env[], char *var)
{
	int	equal_pos;

	equal_pos = find_char(var, '=');
	if (equal_pos == -1 && env_find_var(env, var) == -1)
		env = env_add(env, var, NULL);
	else
	{
		env = env_add(env, ft_strndup(var, equal_pos),
				ft_strdup(&var[equal_pos + 1]));
	}
}

void	export(char *env[], char *args[], int fd)
{
	int		i;
	char	*var;

	g_error = 0;
	if (array_len(args) == 1)
		print_export(env, fd);
	var = ft_strndup(args[1], find_char(args[1], '='));
	i = 1;
	while (args[i] != NULL)
	{
		export_var(env, args[i]);
		i++;
	}
}
