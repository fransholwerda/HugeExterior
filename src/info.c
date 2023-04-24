/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 13:12:27 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/24 14:14:13 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cmds_struct_utils.h"
#include "env_copy.h"
#include "ft_strdup.h"
#include "ft_strlen.h"
#include "ft_strjoin.h"
#include "stop.h"
#include "structs.h"

t_info	*init_info(char *argv[], char *env[])
{
	t_info	*info;

	(void)argv;
	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		stop("init_info: ");
	info->prompt = ft_strdup("minishell> ");
	info->env = env_copy(env);
	info->cmds = NULL;
	return (info);
}

void	free_info(t_info *info)
{
	if (info)
	{
		if (info->prompt)
			free(info->prompt);
		if (info->cmds)
			free_cmds(info->cmds);
		info->prompt = NULL;
		info->cmds = NULL;
		free(info);
		info = NULL;
	}
}
