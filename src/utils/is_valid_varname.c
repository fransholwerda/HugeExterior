/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_valid_varname.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 17:32:03 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/22 17:37:44 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "enums.h"
#include "ft_is_al_under.h"

int	is_valid_varname(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && ft_is_al_under(str[0]) == False)
			return (False);
		else if (i > 0 && ft_is_al_under_num(str[i]) == False)
			return (False);
		i++;
	}
	return (True);
}
