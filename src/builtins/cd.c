/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 20:32:04 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/14 21:58:54 by ahorling      ########   odam.nl         */
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

static char	*get_env_var_no_free(char *env[], char *var)
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
			return (content);
		}
		i++;
	}
	return (ft_strdup(""));
}

static void	change_to_home(t_metainfo *info, char *pwd)
{
	chdir(get_env_var_no_free(info->envp, "HOME"));
	pwd = ft_strjoin("PWD=", getcwd(pwd, 1024 * sizeof(char)));
	info->envp = export_var(info->envp, pwd);
	free(pwd);
}

static void	change_non_home(t_commands *commands, t_metainfo *info, char *pwd)
{
	if (chdir(commands->args[1]) != 0)
	{
		write(2, "minishell: cd: ", 16);
		write(2, commands->args[1], ft_strlen(commands->args[1]));
		write(2, ": No such file or directory\n", 28);
		g_error = 1;
	}
	else
	{
		pwd = ft_strjoin("PWD=", getcwd(pwd, 1024 * sizeof(char)));
		info->envp = export_var(info->envp, pwd);
		free(pwd);
	}
}

static void	cd(t_commands *commands, t_metainfo *info)
{
	char	*pwd;

	g_error = 0;
	pwd = ft_strjoin("OLDPWD=", get_env_var_no_free(info->envp, "PWD"));
	info->envp = export_var(info->envp, pwd);
	free(pwd);
	if (!commands->args[1] || (commands->args[1][0] == '~' && !commands->args[1][1]))
		change_to_home(info, pwd);
	else
		change_non_home(commands, info, pwd);
}

int		execute_cd(t_commands *commands, t_metainfo *info)
{
	cd(commands, info);
	return (0);
}
