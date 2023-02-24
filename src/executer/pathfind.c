/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pathfind.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:38:35 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/19 19:30:18 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "structs.h"
#include "ft_split.h"
#include "utils.h"
#include "errors.h"

static char	**get_paths(t_metainfo *info)
{
	int		i;
	char	**paths;

	i = 0;
	while (info->envp[i])
	{
		if (ft_strncmp(info->envp[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	paths = ft_split(info->envp[i], ':');
	if (!paths)
		env_error();
	return (paths);
}

char	*find_path(t_metainfo *info, t_commands *commands)
{
	int		i;
	char	*temp;
	char	**paths;
	char	*joined_command;
	char	*final_command;

	paths = get_paths(info);
	i = 0;
	while (paths[i] && joined_command != '\0')
	{
		temp = ft_strjoin("/", joined_command);
		final_command = ft_strjoin(paths[i], temp);
		free(temp);
		if (access(final_command, F_OK) == 0)
		{
			free(joined_command);
			return(final_command);
		}
		free(final_command);
		i++;
	}
	path_error();
	return ("path finding failed");
}
