/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_split.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 13:25:31 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/17 15:48:30 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split[i]);
	split[i] = NULL;
	free(split);
	split = NULL;
}
