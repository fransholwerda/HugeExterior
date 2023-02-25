/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 13:12:27 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/25 17:47:53 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env_copy.h"
#include "ft_strlen.h"
#include "ft_strjoin.h"
#include "stop.h"
#include "structs.h"

static char	*get_prompt(char *program_name)
{
	char			*prompt;
	unsigned int	i;

	prompt = NULL;
	i = ft_strlen(program_name) - 1;
	while (i > 0)
	{
		if (program_name[i] == '/')
			prompt = ft_strjoin(&program_name[i + 1], "> ");
		i--;
	}
	return (prompt);
}

t_info	*init_info(char *argv[], char *env[])
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		stop("init_info: ");
	info->prompt = get_prompt(argv[0]);
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
			free(info->cmds); //FREE ALL CMDS
		free(info);
	}
}
