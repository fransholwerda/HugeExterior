/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 14:27:44 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/14 13:54:11 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

void	termion(void);
void	termioff(void);
void	redirect_signal(int mode);

#endif
