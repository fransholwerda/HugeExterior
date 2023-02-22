/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 15:13:46 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/22 18:00:11 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_putendl_fd.h"

extern int	g_error;

void	env(char *envp[], int fd)
{
	int	i;

	g_error = 0;
	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], fd);
		i++;
	}
}
