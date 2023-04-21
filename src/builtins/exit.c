/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/10 18:21:01 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/21 16:51:56 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs.h"

extern int	g_error;

void	mini_exit(t_commands *commands)
{
	if (!commands->prev && !commands->next)
		write(2, "exit\n", 5);
	exit(g_error % 256);
}
