/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/10 18:21:01 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/23 16:22:06 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_atoi.h"
#include "ft_strlen.h"
#include "structs.h"

extern int	g_error;

static int	validate_exit_args(char **args)
{
	int	i;

	i = 0;
	while (args[1] && args[1][i])
	{
		if (i == 0 && (args[1][i] == '-' || args[1][i] == '+'))
			i++;
		if (args[1][i] < '0' || args[1][i] > '9')
		{
			write(2, "minishell: exit: ", 17);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": numeric argument required\n", 28);
			g_error = 255;
			return (0);
		}
		i++;
	}
	if (args[1] && args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		g_error = 1;
		return (-1);
	}
	return (1);
}

void	mini_exit(t_commands *commands)
{
	int	return_value;

	if (access(".heredoc0", F_OK) == 0)
		unlink(".heredoc0");
	return_value = validate_exit_args(commands->args);
	if (return_value == 1 && commands->args[1])
		g_error = ft_atoi(commands->args[1]);
	else if (return_value == -1)
		return ;
	if (!commands->prev && !commands->next)
		write(2, "exit\n", 5);
	exit(g_error % 256);
}
