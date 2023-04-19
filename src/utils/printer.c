/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 12:58:00 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/19 13:12:29 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_strlen.h"

extern int	g_error;

void	*syntax(char *prompt, char *token)
{
	g_error = 258;
	write(2, prompt, ft_strlen(prompt));
	write(2, "syntax error near unexpected token '", 36);
	if (token)
		write(2, token, ft_strlen(token));
	else
		write(2, "newline", 7);
	write(2, "'\n", 2);
	return (NULL);
}
