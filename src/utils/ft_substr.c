/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 16:10:23 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/07 12:24:37 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

char	*ft_substr(char const *s, int start, int len)
{
	char	*substr;
	int		i;

	if (len > ft_strlen(s))
		len = ft_strlen(s);
	substr = malloc((len + 1) * sizeof(char));
	if (substr == NULL || s == NULL)
		malloc_stop("malloc_ft_substr");
	if (start >= ft_strlen(s))
	{
		substr[0] = '\0';
		return (substr);
	}
	i = 0;
	while (i < len && (s[start + i] != '\0'))
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
