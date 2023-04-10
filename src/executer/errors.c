/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 04:58:09 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/10 18:17:29 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "structs.h"
#include "utils/ft_strlen.h"

extern int	g_error;

void	path_error(t_commands *commands)
{
	write(2, "minishell: ", 11);
	write(2, commands->args[0], ft_strlen(commands->args[0]));
	write(2, ": command not found\n", 20);
	g_error = 127;
	exit(g_error);
}

void	fork_error()
{
	printf("Error while executing fork\n");
	exit(g_error);
}

void	pipe_error()
{
	printf("Error while creating pipe\n");
	exit(g_error);
}

void	dupe_error()
{
	printf("Error using dup2 function\n");
	exit(g_error);
}

void	execute_error()
{
	printf("Error executing path. Either command not recognized or function failed\n");
	exit(g_error);
}

void	env_error()
{
	printf("Error getting the environment array\n");
	exit(g_error);
}

void	global_error()
{
	// printf("This is a stand in for the global error code.\n");
	exit(g_error);
}