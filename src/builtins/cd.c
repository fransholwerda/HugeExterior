/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 20:32:04 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/21 16:48:51 by ahorling      ########   odam.nl         */
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
	char *buffer;
	char *home;
	
	home = get_env_var_no_free(info->envp, "HOME");
	if (chdir(home) != 0)
	{
		write(info->outfilefd, "minishell: cd: ", 16);
		write(info->outfilefd, "HOME", 4);
		write(info->outfilefd, ": No such file or directory\n", 28);
		g_error = 1;
		free(pwd);
		free(home);
		return ;
	}
	free(pwd);
	buffer = malloc(sizeof(char) * 10240);
	pwd = ft_strjoin("PWD=", getcwd(buffer, 1024 * sizeof(char)));
	free(buffer);
	info->envp = export_var(info->envp, pwd);
	free(pwd);
	free(home);
}

static void	change_non_home(t_commands *commands, t_metainfo *info, char *pwd)
{
	char *buffer;

	if (chdir(commands->args[1]) != 0)
	{
		write(info->outfilefd, "minishell: cd: ", 16);
		write(info->outfilefd, commands->args[1], ft_strlen(commands->args[1]));
		write(info->outfilefd, ": No such file or directory\n", 28);
		g_error = 1;
		free(pwd);
	}
	else
	{
		free(pwd);
		buffer = malloc(10240 * sizeof(char));
		pwd = ft_strjoin("PWD=", getcwd(buffer, 10240 * sizeof(char)));
		free(buffer);
		info->envp = export_var(info->envp, pwd);
		free(pwd);
	}
}

void	cd(t_commands *commands, t_metainfo *info)
{
	char	*pwd;
	char	*oldpwd;

	g_error = 0;
	oldpwd = get_env_var_no_free(info->envp, "PWD");
	pwd = ft_strjoin("OLDPWD=", oldpwd);
	info->envp = export_var(info->envp, pwd);
	free(oldpwd);
	if (!commands->args[1]
		|| (commands->args[1][0] == '~' && !commands->args[1][1]))
		change_to_home(info, pwd);
	else
		change_non_home(commands, info, pwd);
}
