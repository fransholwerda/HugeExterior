/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 14:12:17 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/07 12:22:27 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_strlen.h"
#include "stop.h"

char	*ft_strdup(const char *s)
{
	char	*sdup;
	int		i;

	sdup = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (sdup == NULL)
		malloc_stop("malloc_ft_strdup");
	i = 0;
	while (i < ft_strlen(s))
	{
		sdup[i] = s[i];
		i++;
	}
	sdup[i] = '\0';
	return (sdup);
}
