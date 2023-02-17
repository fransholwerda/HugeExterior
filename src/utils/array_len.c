/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array_len.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 17:26:15 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/15 17:26:24 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	array_len(char *array[])
{
	int	count;

	count = 0;
	while (array[count])
		count++;
	return (count);
}
