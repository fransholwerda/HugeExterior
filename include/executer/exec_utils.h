/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 21:13:52 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/21 21:00:31 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include "structs.h"

char	**exec_single_builtin(t_commands *commands, t_metainfo *info);
void	exec_single_command(t_commands *commands, t_metainfo *info,
			int pipe1[2], int pipe2[2]);
void	exec_multiple_commands(t_commands *commands, t_metainfo *info,
			int pipe1[2], int pipe2[2]);
int		get_exit_code(t_metainfo *info, int status);

#endif