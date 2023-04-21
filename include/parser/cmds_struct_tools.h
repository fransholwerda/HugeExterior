/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_struct_tools.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 17:13:32 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/17 20:09:33 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_STRUCT_TOOLS_H
# define CMDS_STRUCT_TOOLS_H

# include <stdbool.h>
# include "structs.h"

void		add_infile(t_commands *cmds, char *infile, bool hd);
void		add_outfile(t_commands *cmds, char *outfile, bool append);
void		add_args(t_commands *cmds, char *arg);

#endif
