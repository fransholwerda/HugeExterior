/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   termios.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/16 17:04:30 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/16 17:06:00 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>

void	termion(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
}

void	termioff(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
}
