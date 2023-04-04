/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/02 13:05:46 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/04 13:50:20 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "enums.h"
#include "ft_is_al_under.h"
#include "ft_strlen.h"

extern int	g_error;

int	export_validate(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if ((i == 0 && ((str[0] >= '0' && str[0] <= '9') || (str[0] == '=')))
			|| ft_is_al_under_num(str[i]) == False)
		{
			if (g_error == 0)
			{
				g_error = 1;
				write(2, "1minishell: export: '", 20);
				write(2, str, ft_strlen(str));
				write(2, "': is not a valid identifier\n", 29);
			}
			return (False);
		}
		i++;
	}
	return (True);
}
