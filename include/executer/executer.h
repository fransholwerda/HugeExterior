/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/08 16:47:26 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/20 16:47:40 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "structs.h"

char	**executer(t_commands *commands, char **envp);
void	execute_child(t_commands *commands, t_metainfo *info, int pipefd[2]);
int		begin_fork(t_commands *commands, t_metainfo *info,
			int pipe1[2], int pipe2[2]);

#endif
