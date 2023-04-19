/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 04:58:09 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/19 20:53:57 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_strlen.h"
#include "structs.h"

extern int	g_error;

void	path_error(t_commands *commands)
{
	write(2, "minishell: ", 12);
	write(2, commands->args[0], ft_strlen(commands->args[0]));
	write(2, ": command not found\n", 21);
	g_error = 127;
	exit(g_error);
}

void	infile_errors(t_commands *commands)
{
	if (access(commands->infile->name, F_OK) != 0)
	{
		write(2, "minishell: ", 12);
		write(2, commands->infile->name, ft_strlen(commands->infile->name));
		write(2, ": No suchfile or directory\n", 28);
		g_error = 1;
		exit(g_error);
	}
	else if (access(commands->infile->name, R_OK) != 0)
	{
		write(2, "minishell: ", 12);
		write(2, commands->infile->name, ft_strlen(commands->infile->name));
		write(2, ": Permission denied\n", 21);
		g_error = 1;
		exit(g_error);
	}
}

void	outfile_error(t_commands *commands)
{
	write(2, "minishell: ", 12);
	write(2, commands->outfile->name, ft_strlen(commands->outfile->name));
	write(2, ": Permission denied\n", 21);
	g_error = 1;
	exit(g_error);
}

void	fork_error(void)
{
	write(2, "minishell: ", 12);
	write(2, "fork: ", 7);
	write(2, "Resource temporarily unavailable\n", 34);
	g_error = 1;
	exit(g_error);
}

void	env_error(void)
{
	write(2, "Failure to split env in in pathfind\n", 37);
	g_error = 1;
	exit(g_error);
}
