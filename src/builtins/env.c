/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 15:13:46 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/24 18:50:19 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_putendl_fd.h"

extern int	g_error;

void	env(char *envp[])
{
	int	i;

	g_error = 0;
	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
}
