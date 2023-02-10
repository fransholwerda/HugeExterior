/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 13:05:07 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/01/03 13:14:58 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "structs.h"
#include "ft_strlen.h"

extern int	g_error;

void	stop(char *str)
{
	if (str)
	{
		write(2, "minishell: ", 11);
		perror(str);
	}
	else
		perror("minishell: ");
	exit(g_error);
}

void	malloc_stop(char *str)
{
	g_error = 1;
	stop(str);
}
