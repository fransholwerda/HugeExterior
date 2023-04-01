/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   join_three.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 18:43:07 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/01 18:43:26 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_strjoin.h"

char	*join_three(char *s1, char *s2, char *s3)
{
	char	*new_str;
	char	*temp;

	new_str = ft_strjoin(s1, s2);
	temp = new_str;
	new_str = ft_strjoin(new_str, s3);
	free(temp);
	return (new_str);
}
