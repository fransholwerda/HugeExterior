/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/08 16:47:26 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/12 22:19:59 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "structs.h"

void	executer(t_commands *commands, char **envp);
int		execute_fork(t_commands *commands, t_metainfo *info);
void	execute_child(t_commands *commands, t_metainfo *info, int pipefd[2]);


#endif