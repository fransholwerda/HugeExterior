/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 16:09:40 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/22 17:59:59 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "enums.h"
#include "env_pop.h"
#include "ft_putendl_fd.h"
#include "ft_putstr_fd.h"
#include "is_valid_varname.h"
#include "structs.h"

extern int	g_error;

void	unset(t_metainfo *info, char *var, int fd)
{
	g_error = 0;
	if (is_valid_varname(var) == False)
	{
		ft_putstr_fd("minishell: unset: '", fd);
		ft_putstr_fd(var, fd);
		ft_putendl_fd("': not a valid identifier", fd);
		g_error = 1;
	}
	else
		info->envp = env_pop(info->envp, var);
}
