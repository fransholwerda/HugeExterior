/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 20:26:13 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/23 20:29:14 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strchr(const char *str, int c)
{
	char	*input;

	input = (char *)str;
	while (*input != '\0')
	{
		if (*input == (char)c)
			return (input);
		input++;
	}
	if ((char)c == '\0')
		return (input);
	return (NULL);
}
