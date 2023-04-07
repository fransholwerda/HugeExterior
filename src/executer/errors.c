/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 04:58:09 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/07 21:28:08 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

extern int	g_error;

void	path_error()
{
	printf("Error finding or building path\n");
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