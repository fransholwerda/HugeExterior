/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 17:19:34 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/24 15:14:13 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_putstr_fd.h"
#include "ft_strncmp.h"
#include "structs.h"

extern int	g_error;

static int	flag_check(char *args[])
{
	int		i;
	int		j;

	i = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 2;
		while (args[i][j] && args[i][j] == 'n')
			j++;
		if (args[i][j])
			return (i);
		i++;
	}
	return (i);
}

void	echo(t_commands *commands, int fd)
{
	bool	newline;
	int		i;

	i = flag_check(commands->args);
	newline = true;
	if (i > 1)
		newline = false;
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
