/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_al_under.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 17:49:12 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/23 15:57:01 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "enums.h"

int	ft_is_al_under(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (True);
	if (c >= 'a' && c <= 'z')
		return (True);
	if (c == '_')
		return (True);
	return (False);
}

int	ft_is_al_under_num(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (True);
	if (c >= 'a' && c <= 'z')
		return (True);
	if (c == '_')
		return (True);
	if (c >= '0' && c <= '9')
		return (True);
	return (False);
}
