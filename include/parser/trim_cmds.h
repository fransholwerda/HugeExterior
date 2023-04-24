/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trim_cmds.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 17:30:32 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/24 13:39:10 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIM_CMDS_H
# define TRIM_CMDS_H

# include "structs.h"

void	find_trim(char **split, int i);
void	trim_split_cmds(char **split);
void	trim_cmds(t_commands *cmds);

#endif
