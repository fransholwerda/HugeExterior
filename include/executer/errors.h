/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 22:13:10 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/19 17:19:38 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "structs.h"

void	path_error(t_commands *commands);
void	infile_errors(t_commands *commands);
void	outfile_error(t_commands *commands);
void	env_error(void);
void	fork_error(void);

#endif