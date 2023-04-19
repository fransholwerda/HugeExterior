/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 20:21:24 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/19 17:44:47 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "errors.h"
#include "pathfind.h"
#include "structs.h"

extern int	g_error;

void	close_pipes(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	closefds(t_metainfo *info)
{
	if (info->infilefd > 2)
		close(info->infilefd);
	if (info->outfilefd > 2)
		close(info->outfilefd);
}

void	manage_infiles(t_commands *commands, t_metainfo *info)
{
	if (commands->infile)
	{
		while (commands->infile)
		{
			if (access(commands->infile->name, F_OK | R_OK) != 0)
				infile_errors(commands);
			else if (commands->infile->hd == true && commands->infile->next)
			{
				commands->infile = commands->infile->next;
				continue ;
			}
			else
				info->infilefd = open(commands->infile->name, commands->infile->mode);
			if (commands->infile->hd == true)
				unlink(commands->infile->name);
			if (commands->infile->next)
				close(info->infilefd);
			commands->infile = commands->infile->next;
		}
	}
	else
		info->infilefd = STDIN_FILENO;
}

void	manage_outfiles(t_commands *commands, t_metainfo *info)
{
	if (commands->outfile)
	{
		while (commands->outfile)
		{
			if (access(commands->outfile->name, F_OK) != 0)
				info->outfilefd = open(commands->outfile->name, O_RDWR | O_CREAT, 0655);
			else if (access(commands->outfile->name, W_OK) == 0)
				info->outfilefd = open(commands->outfile->name, commands->outfile->mode);
			else
				outfile_error(commands);
			commands->outfile = commands->outfile->next;
		}
	}
	else
		info->outfilefd = STDOUT_FILENO;
}
