/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forkingfuckery.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 17:21:57 by ahorling      #+#    #+#                 */
/*   Updated: 2023/01/11 17:44:53 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main()
{
	int x = 0;
	if (fork() == 0)
	{
		x++;
		printf("I am the child, and x has the value: %d\n", x);
	}
	printf("x has a value of %d\n", x);
	return (0);
}