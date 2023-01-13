/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testmain.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 21:42:27 by ahorling      #+#    #+#                 */
/*   Updated: 2023/01/13 20:54:32 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "includes/structs.h"

int	main()
{
	t_commands	commands;
	char	*path;
	char	*command;
	char	*flags;
	int		i;

	i = 0;
	path = "";
	command = "echo";
	flags = "";

	commands.list_of_commands[0] = command;
	commands.list_of_commands[1] =
	commands.list_of_commands[2] =
	while (commands.list_of_commands[i])
		printf("%s\n", commands.list_of_commands[i]);
		i++;
	return (0);
}