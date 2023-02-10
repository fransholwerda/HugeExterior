/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 15:22:59 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/01/03 15:52:55 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_strlen.h"
#include "stop.h"

char	*ft_strndup(const char *s, int n)
{
	char	*sdup;
	int		len;
	int		i;

	if (n <= 0)
		return (NULL);
	sdup = malloc((n + 1) * sizeof(char));
	if (!sdup)
		malloc_stop("malloc_strndup");
	len = ft_strlen(s);
	i = 0;
	while (i < (n) && i < (len))
	{
		sdup[i] = s[i];
		i++;
	}
	sdup[i] = '\0';
	return (sdup);
}
