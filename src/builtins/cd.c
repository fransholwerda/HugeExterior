/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 20:32:04 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/12 22:16:36 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include "builtins/export.h"
#include "builtins/export_utils.h"
#include "utils/ft_strncmp.h"
#include "utils/ft_strdup.h"
#include "utils/ft_strjoin.h"
#include "utils/ft_strlen.h"
#include "structs.h"

extern int	g_error;

static char	*get_env_var(char *env[], char *var)
{
	int		i;
	char	*content;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& env[i][ft_strlen(var)] == '=')
		{
			content = ft_strdup(&env[i][ft_strlen(var) + 1]);
			// free(var);
			return (content);
		}
		i++;
	}
	free(var);
	return (ft_strdup(""));
}

void	cd(t_commands *commands, t_metainfo *info)
{
	char	*oldpwd;
	char	buf[1024];
	char	*newpwd;

	oldpwd = ft_strjoin("OLDPWD=", get_env_var(info->envp, "PWD"));
	info->envp = export_var(info->envp, oldpwd);
	if (!commands->args[1] || commands->args[1][0] == '~')
	{
		chdir(get_env_var(info->envp, "HOME"));
		newpwd = ft_strjoin("PWD=", getcwd(buf, sizeof(buf)));
		info->envp = export_var(info->envp, newpwd);
	}
	else
	{
		if (chdir(commands->args[1]) != 0)
		{
			write(2, "minishell: cd: ", 16);
			write(2, commands->args[1], ft_strlen(commands->args[1]));
			write(2, ": No such file or directory", 27);
		}
		newpwd = ft_strjoin("PWD=", getcwd(buf, sizeof(buf)));
		info->envp = export_var(info->envp, newpwd);
	}
}