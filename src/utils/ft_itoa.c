/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:06:44 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/03/04 16:42:39 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "stop.h"

static int	count_digits(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	fill_nbr(char *nbr, int n, int minus, int digits)
{
	nbr[digits] = '\0';
	digits--;
	if (minus == 1)
	{
		if (n == -2147483648)
		{
			nbr[digits] = '8';
			n = -214748364;
			digits--;
		}
		n *= -1;
	}
	while (digits >= 0)
	{
		if (digits == 0 && minus == 1)
			nbr[0] = '-';
		else
		{
			nbr[digits] = (n % 10) + 48;
			n /= 10;
		}
		digits--;
	}
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		digits;
	int		minus;

	digits = count_digits(n);
	nbr = malloc((digits + 1) * sizeof(char));
	if (nbr == NULL)
		malloc_stop("malloc_ft_itoa");
	minus = 0;
	if (n < 0)
		minus = 1;
	fill_nbr(nbr, n, minus, digits);
	return (nbr);
}
