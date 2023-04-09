/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_struct_tools.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 17:15:07 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/09 18:28:09 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_STRUCT_TOOLS_H
# define FILE_STRUCT_TOOLS_H

# include <stdbool.h>
# include "structs.h"

t_file	*new_file(char *filename, int mode, int mode2, bool hd);
t_file	*file_add_back(t_file *file, t_file *file_new);

#endif
