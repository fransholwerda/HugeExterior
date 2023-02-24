/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_sort.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 12:50:05 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/22 15:05:51 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "array_len.h"
#include "ft_strcmp.h"

void	array_sort(char *array[])
{
	char	*temp;
	int		i;
	int		j;
	int		len;

	len = array_len(array);
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
