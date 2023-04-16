/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 17:19:34 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/16 16:09:18 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_putstr_fd.h"
#include "ft_strncmp.h"
#include "structs.h"

extern int	g_error;

void	echo(t_commands *commands, int fd)
{
	bool	newline;
	int		i;

	i = 1;
	newline = true;
	if (commands->args[i] && ft_strncmp(commands->args[i], "-n", 2) == 0)
	{
		newline = false;
		i++;
	}
	while (commands->args[i])
	{
		ft_putstr_fd(commands->args[i], fd);
		if (commands->args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (newline == true)
		ft_putstr_fd("\n", fd);
	g_error = 0;
}
