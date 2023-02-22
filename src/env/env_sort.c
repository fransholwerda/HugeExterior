/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_sort.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 12:50:05 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/22 15:00:06 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "array_len.h"
#include "ft_strcmp.h"

void	env_sort(char *env[])
{
	char	*temp;
	int		i;
	int		j;
	int		len;

	len = array_len(env);
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
