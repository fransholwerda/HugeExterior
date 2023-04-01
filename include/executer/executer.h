/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/08 16:47:26 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/01 16:04:43 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "structs.h"

char	**executer(t_commands *commands, char **envp);
int		execute_fork(t_commands *commands, t_metainfo *info);
void	execute_child(t_commands *commands, t_metainfo *info, int pipefd[2]);

#endif
