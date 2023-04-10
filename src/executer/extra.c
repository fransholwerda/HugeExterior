/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 20:21:24 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/10 18:12:50 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "executer/pathfind.h"
#include "structs.h"
#include "executer/errors.h"

void	close_pipes(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	manage_infiles(t_commands *commands, t_metainfo *info)
{
	info->path = find_path(info, commands);
	if (commands->infile)
	{
		while (commands->infile)
		{
			// if (commands->infile->hd == true)
			// {
				
			// }
			if (access(commands->infile->name, F_OK) != 0)
			{
				printf("minishell: %s: No suchfile or directory\n", commands->infile->name);
				return(global_error());
			}
			else if (access(commands->infile->name, R_OK) != 0)
			{
				printf("minishell: %s: Permission denied\n", commands->infile->name);
				return(global_error());
			}
			else
				info->infilefd = open(commands->infile->name, commands->infile->mode);
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
					info->outfilefd = open(commands->outfile->name, O_RDWR|O_CREAT, 0655);
			else if (access(commands->outfile->name, W_OK) == 0)
					info->outfilefd = open(commands->outfile->name, commands->outfile->mode);
			else
			{
				printf("minishell: %s: Permission denied\n", commands->outfile->name);
				return(global_error());
			}
			commands->outfile = commands->outfile->next;
		}
	}
	else
		info->outfilefd = STDOUT_FILENO;
}