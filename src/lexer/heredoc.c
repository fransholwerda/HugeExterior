/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/04 13:10:35 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/03/04 17:57:29 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_itoa.h"
#include "ft_strcmp.h"
#include "ft_strlen.h"
#include "ft_strjoin.h"
#include "readline/readline.h"

extern int	g_error;

static char	*get_hd_filename(int pipe_count)
{
	char	*pipe_count_str;
	char	*filename;

	pipe_count_str = ft_itoa(pipe_count);
	filename = ft_strjoin(".heredoc", pipe_count_str);
	free(pipe_count_str);
	return (filename);
}

static char	*expand_heredoc(char *env[], char *str)
{
	int	pos;
	int	end;

	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '$' && str[pos + 1] != ' ' && str[pos + 1] != '$'
			&& str[pos + 1] != '\0')
		{

		}
	}
}

char	*go_heredoc(char *env[], char *eof, int pipe_count)
{
	int		fd;
	char	*filename;
	char	*str;
	//Handle Signals?

	(void)env;
	filename = get_hd_filename(pipe_count);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL); //and do some other shit
	str = readline("> ");
	while (ft_strcmp(str, eof) != 0)
	{
		str = expand_heredoc(env, str);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	close(fd);
	free(str);
	return (filename);
}
