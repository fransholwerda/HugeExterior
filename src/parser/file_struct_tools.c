/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_struct_tools.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 17:12:02 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/24 12:25:01 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_strdup.h"
#include "stop.h"
#include "structs.h"

void	free_file(t_file *file)
{
	t_file	*tmp;

	while (file)
	{
		tmp = file->next;
		if (file->name)
		{
			free(file->name);
			file->name = NULL;
		}
		free(file);
		file = tmp;
	}
}

t_file	*new_file(char *filename, int mode, int mode2, bool hd)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		malloc_stop("malloc_new_file");
	if (hd == true)
		file->name = filename;
	else
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
