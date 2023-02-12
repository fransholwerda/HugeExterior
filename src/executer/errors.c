/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 04:58:09 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/12 22:15:22 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	path_error()
{
	printf("Error finding or building path");
	exit();
}

void	fork_error()
{
	printf("Error while executing fork");
	exit();
}

void	pipe_error()
{
	printf("Error while creating pipe");
	exit();
}

void	dupe_error()
{
	printf("Error using dup2 function");
	exit();
}

void	execute_error()
{
	printf("Error executing path. Either command not recognized or function failed");
	exit();
}