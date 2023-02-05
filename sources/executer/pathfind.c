/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pathfind.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:38:35 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/05 21:56:25 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/structs.h"

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
	paths = ft_split(info->envp[i][5], ':');
	if (!paths)
		environment_error();
	return (paths);
}

char	*find_path(t_metainfo *info, t_commands *commands)
{
	int		i;
	char	*temp;
	char	**paths;
	char	*joined_command;
	char	*final_command;

	i = 0;
	paths = get_paths(info);
	joined_command = ft_strjoin(commands->list_of_commands[0], commands->list_of_commands[1]);
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