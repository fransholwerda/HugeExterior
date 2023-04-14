/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 15:15:33 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/14 22:12:08 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "ft_putendl_fd.h"

extern int	g_error;

static void	pwd(int fd)
{
	char	buf[1024];

	g_error = 0;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		g_error = 1;
		perror("pwd");
	}
	else
		ft_putendl_fd(buf, fd);
}

int		execute_pwd(int fd)
{
	pwd(fd);
	return (0);
}
