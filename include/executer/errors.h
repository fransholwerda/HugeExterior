/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 22:13:10 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/17 19:46:50 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

void	path_error();
void	fork_error();
void	pipe_error();
void	dupe_error();
void	execute_error();
void	global_error();
void	env_error();

#endif