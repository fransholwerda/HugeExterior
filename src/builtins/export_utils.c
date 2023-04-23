/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/02 13:05:46 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/23 15:04:27 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "enums.h"
#include "ft_is_al_under.h"
#include "ft_strlen.h"

extern int	g_error;

static void	set_export_error(char *str)
{
	if (g_error == 0)
	{
		g_error = 1;
		write(2, "minishell: export: '", 20);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 26);
	}
}

int	export_validate(char *str)
{
	int	i;

	if (ft_strlen(str) == 0)
	{
		set_export_error(str);
		return (False);
	}
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if ((i == 0 && ((str[0] >= '0' && str[0] <= '9') || (str[0] == '=')))
			|| ft_is_al_under_num(str[i]) == False)
		{
			set_export_error(str);
			return (False);
		}
		i++;
	}
	return (True);
}
