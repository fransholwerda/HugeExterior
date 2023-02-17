/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 13:49:12 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/17 13:49:24 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_strlen.h"

void	ft_putendl_fd(char *string, int fd)
{
	int	len;

	len = ft_strlen(string);
	if (fd >= 0 && string != NULL)
	{
		write(fd, string, len);
		write(fd, "\n", 1);
	}
}
