/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_struct_tools.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 17:12:02 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/14 13:14:33 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"
#include "structs.h"

t_file	*new_file(char *filename, int mode)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		malloc_stop("malloc_new_file");
	file->name = ft_strdup(filename);
	file->mode = mode;
	file->next = NULL;
	return (file);
}

t_file	*file_add_back(t_file *file, char *filename, int mode)
{
	t_file	*head;

	head = file;
	while (file->next)
		file = file->next;
	file->next = new_file(filename, mode);
	return (head);
}
