/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pathfind.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:38:35 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/24 17:13:24 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "free_split.h"
#include "exec_utils.h"
#include "ft_split.h"
#include "utils.h"
#include "errors.h"

extern int	g_error;

static void	path_not_set(t_commands *commands)
{
	write(2, "minishell: ", 12);
	write(2, commands->args[0], ft_strlen(commands->args[0]));
	write(2, ": No such file or directory\n", 29);
	g_error = 127;
	exit(g_error);
}

static char	**get_paths(t_metainfo *info, t_commands *commands)
{
	int		i;
	char	**paths;
	char	*temp;

	i = 0;
	while (info->envp[i])
	{
		if (ft_strncmp(info->envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (info->envp[i] == NULL)
	{
		paths = NULL;
		if (access(commands->args[0], F_OK) != 0)
			path_not_set(commands);
		return (paths);
	}
	temp = ft_substr(info->envp[i], 5, ft_strlen(info->envp[i]));
	paths = ft_split(temp, ':');
	free(temp);
	return (paths);
}

char	*find_path(t_metainfo *info, t_commands *commands)
{
	int		i;
	char	*temp;
	char	**paths;
	char	*final_command;

	paths = get_paths(info, commands);
	i = 0;
	if (!commands->args || paths == NULL)
		return (NULL);
	while (paths[i] && commands->args[0])
	{
		temp = ft_strjoin("/", commands->args[0]);
		final_command = ft_strjoin(paths[i], temp);
		free(temp);
		if (access(final_command, F_OK) == 0)
		{
			free_split(paths);
			return (final_command);
		}
		free(final_command);
		i++;
	}
	free_split(paths);
	return (NULL);
}
