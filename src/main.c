/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 14:50:15 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/17 19:54:07 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "info.h"
#include "signal.h"
#include "structs.h"
#include "termine.h"
#include "minishell.h"

int	g_error = 0;

int	main(int argc, char **argv, char *env[])
{
	t_info	*info;

	if (argc != 1)
		return (EXIT_FAILURE);
	info = init_info(argv, env);
	termion();
	redirect_signal(1);
	minishell(info);
	termioff();
	free_info(info);
	return (EXIT_SUCCESS);
}
