/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 12:58:00 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/07 13:40:29 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_strlen.h"

void	syntax(char *prompt, char *token)
{
	write(2, prompt, ft_strlen(prompt));
	write(2, "syntax error near unexpected token '", 36);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
}
