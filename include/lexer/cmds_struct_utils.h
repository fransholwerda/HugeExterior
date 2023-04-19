/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_struct_utils.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 20:09:35 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/17 20:10:00 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_STRUCT_UTILS_H
# define CMDS_STRUCT_UTILS_H

# include "structs.h"

void		free_cmds(t_commands *cmds);
t_commands	*new_cmds(t_commands *prev);
t_commands	*last_cmd(t_commands *cmds);

#endif
