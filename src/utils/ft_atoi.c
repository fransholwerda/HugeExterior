/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 10:46:51 by fholwerd      #+#    #+#                 */
/*   Updated: 2022/12/20 14:03:37 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	of_check(long int value, int minus, const char c)
{
	if (((value * 10 * minus) > INT_MAX && c > 55)
		|| (value * 10 * minus) >= INT_MAX)
		return (-1);
	else if (((value * 10 * minus) < INT_MIN && c > 56)
		|| (value * 10 * minus) <= INT_MIN)
		return (0);
	else
		return (1);
}

int	ft_atoi(const char *nptr)
{
	long int	value;
	int			minus;
	int			i;

	value = 0;
	minus = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		if (of_check(value, minus, nptr[i]) < 1)
			return (-2);
		value = (value * 10) + (nptr[i] - 48);
		i++;
	}
	return ((int)(value * minus));
}
