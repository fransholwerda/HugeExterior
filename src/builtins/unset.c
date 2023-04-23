/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 16:09:40 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/23 16:03:20 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "enums.h"
#include "env_pop.h"
#include "ft_putendl_fd.h"
#include "ft_putstr_fd.h"
#include "ft_strdup.h"
#include "is_valid_varname.h"
#include "structs.h"

extern int	g_error;

void	unset(t_metainfo *info, char *args[], int fd)
{
	int	i;

	g_error = 0;
	i = 1;
	while (args[i])
	{
		if (is_valid_varname(args[i]) == False)
		{
			ft_putstr_fd("minishell: unset: '", fd);
			ft_putstr_fd(args[i], fd);
			ft_putendl_fd("': not a valid identifier", fd);
			g_error = 1;
		}
		else
			info->envp = env_pop(info->envp, ft_strdup(args[i]));
		i++;
	}
}
