/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pathfind.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:38:35 by ahorling      #+#    #+#                 */
/*   Updated: 2023/03/08 22:19:27 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "structs.h"
#include "ft_split.h"
#include "utils.h"
#include "errors.h"

static char *build_command(t_metainfo *info, t_commands *commands)
{
	int		i;
	char	temp1;
	char	temp2;
	char	combined_args;

	i = 0;
	combined_args = ft_strdup(commands->args[i]);
	while (commands->args[i + 1])
	{
		temp1 = ft_strjoin(" ", commands->args[i + 1]);
		temp2 = ft_strjoin(combined_args, temp1);
		
	}
}

static char	**get_paths(t_metainfo *info)
{
	int		i;
	char	**paths;
	char	*temp;

	i = 0;
	while (info->envp[i])
	{
		if (ft_strncmp(info->envp[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	temp = ft_substr(info->envp[i], 5, ft_strlen(info->envp[i]));
	paths = ft_split(temp, ':');
	if (!paths)
	{
		free(temp);
		env_error();
	}
	free(temp);
	return (paths);
}

char	*find_path(t_metainfo *info, t_commands *commands)
{
	int		i;
	char	*temp;
	char	**paths;
	char	*final_command;

	paths = get_paths(info);
	i = 0;
	while (paths[i] && commands->args[0] != '\0')
	{
		temp = ft_strjoin("/", commands->args[0]);
		final_command = ft_strjoin(paths[i], temp);
		free(temp);
		if (access(final_command, F_OK) == 0)
			return(final_command);
		free(final_command);
		i++;
	}
//	path_error();
	return ("path finding failed");
}
