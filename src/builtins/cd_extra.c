/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_extra.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 21:50:14 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/24 22:23:55 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "cd.h"
#include "export.h"
#include "ft_strjoin.h"
#include "structs.h"

void	cd_to_non_home(t_metainfo *info, char *buffer, char *oldpwd, char *pwd)
{
	info->envp = export_var(info->envp, oldpwd);
	buffer = malloc(10240 * sizeof(char));
	if (!buffer)
		return ;
	getcwd(buffer, 10240 * sizeof(char));
	if (access(buffer, F_OK) != 0)
	{
		out_of_bounds(buffer, info, oldpwd);
		return ;
	}
	free(oldpwd);
	pwd = ft_strjoin("PWD=", buffer);
	free(buffer);
	info->envp = export_var(info->envp, pwd);
	free(pwd);
}
