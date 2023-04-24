/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 15:15:33 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/24 19:23:40 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_putendl_fd.h"
#include "structs.h"

extern int	g_error;

void	pwd(t_commands *commands, int fd)
{
	char	*buf;

	g_error = 0;
	buf = malloc(10240 * sizeof(char));
	getcwd(buf, 10240 * sizeof(char));
	if (!buf)
	{
		write(2, "getcwd failed", 14);
		g_error = 1;
		if (commands->prev || commands->next)
			exit(g_error);
	}
	else
		ft_putendl_fd(buf, fd);
	free(buf);
}
