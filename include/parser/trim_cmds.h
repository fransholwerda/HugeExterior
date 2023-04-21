/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trim_cmds.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 17:30:32 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/21 12:43:57 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIM_CMDS_H
# define TRIM_CMDS_H

# include "structs.h"

void	trim_split_cmds(char **split);
void	trim_cmds(t_commands *cmds);

#endif
