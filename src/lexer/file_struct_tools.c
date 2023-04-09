/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_struct_tools.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 17:12:02 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/09 18:27:37 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_strdup.h"
#include "stop.h"
#include "structs.h"

t_file	*new_file(char *filename, int mode, int mode2, bool hd)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		malloc_stop("malloc_new_file");
	file->name = ft_strdup(filename);
	file->mode = mode;
	file->mode2 = mode2;
	file->hd = hd;
	file->next = NULL;
	return (file);
}

t_file	*file_add_back(t_file *file, t_file *file_new)
{
	t_file	*head;

	head = file;
	while (file->next)
		file = file->next;
	file->next = file_new;
	return (head);
}
