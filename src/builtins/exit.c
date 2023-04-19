/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/10 18:21:01 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/19 20:58:32 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs.h"

extern int	g_error;

void	mini_exit(t_commands *commands)
{
	g_error = 0;
	if (!commands->prev)
		write(2, "exit\n", 5);
	exit(g_error);
}
