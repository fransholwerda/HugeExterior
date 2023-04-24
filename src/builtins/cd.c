/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 20:32:04 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/24 22:24:51 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "cd_extra.h"
#include "export.h"
#include "export_utils.h"
#include "ft_strdup.h"
#include "ft_strjoin.h"
#include "ft_strlen.h"
#include "ft_strncmp.h"
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

static void	change_to_home(t_metainfo *info, char *oldpwd)
{
	char	*buffer;
	char	*home;
	char	*pwd;

	home = get_env_var_no_free(info->envp, "HOME");
	if (chdir(home) != 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, "HOME not set\n", 13);
		g_error = 1;
		free(oldpwd);
		free(home);
		return ;
	}
	info->envp = export_var(info->envp, oldpwd);
	free(oldpwd);
	buffer = malloc(sizeof(char) * 10240);
	pwd = ft_strjoin("PWD=", getcwd(buffer, 1024 * sizeof(char)));
	free(buffer);
	info->envp = export_var(info->envp, pwd);
	free(pwd);
	free(home);
}

void	out_of_bounds(char *buffer, t_metainfo *info, char *oldpwd)
{
	char	*home;

	home = get_env_var_no_free(info->envp, "HOME");
	if (home[0] == '\0')
	{
		write(2, "listen here you little shit, I'm kicking you out\n", 49);
		free(buffer);
		free(home);
		exit(1);
	}
	else if (home)
	{
		write(2, "Target directory is unaccessible\n", 33);
		write(2, "You seem to have gotten lost, lets send you back $HOME\n", 55);
		free(buffer);
		free(home);
		change_to_home(info, oldpwd);
		return ;
	}
}

static void	non_home(t_commands *commands, t_metainfo *info, char *oldpwd)
{
	char	*buffer;
	char	*pwd;

	pwd = NULL;
	buffer = NULL;
	if (chdir(commands->args[1]) != 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, commands->args[1], ft_strlen(commands->args[1]));
		write(2, ": No such file or directory\n", 28);
		g_error = 1;
		free(oldpwd);
	}
	else
		cd_to_non_home(info, buffer, oldpwd, pwd);
}

void	cd(t_commands *commands, t_metainfo *info)
{
	char	*oldpwd;
	char	*currentpwd;

	g_error = 0;
	currentpwd = get_env_var_no_free(info->envp, "PWD");
	oldpwd = ft_strjoin("OLDPWD=", currentpwd);
	free(currentpwd);
	if (!commands->args[1]
		|| (commands->args[1][0] == '~' && !commands->args[1][1]))
		change_to_home(info, oldpwd);
	else
		non_home(commands, info, oldpwd);
}
