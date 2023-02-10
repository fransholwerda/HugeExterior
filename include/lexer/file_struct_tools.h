/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_struct_tools.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 17:15:07 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/07 17:15:36 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_STRUCT_TOOLS_H
# define FILE_STRUCT_TOOLS_H

# include "structs.h"

t_file	*new_file(char *filename, int mode);
t_file	*file_add_back(t_file *file, char *filename, int mode);

#endif
