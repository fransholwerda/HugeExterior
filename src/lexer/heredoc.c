/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/04 13:10:35 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/12 16:42:46 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "enums.h"
#include "expand_utils.h"
#include "ft_is_al_under.h"
#include "ft_itoa.h"
#include "ft_strcmp.h"
#include "ft_strlen.h"
#include "ft_strjoin.h"
#include "ft_substr.h"
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

static char	*expand_dollar_hd(char *env[], char *str, int pos)
{
	int		end;
	char	*var;
	char	*new_str;

	end = expand_dollar_length(str, pos);
	var = get_env_var(env, ft_substr(str, pos + 1, end - pos));
	new_str = combine_three_strings(str, pos, end + 1, var);
	return (new_str);
}

static char	*expand_heredoc(char *env[], char *str)
{
	int		pos;
	int		skip;

	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '$' && str[pos + 1] != ' ' && str[pos + 1] != '$'
			&& str[pos + 1] != '\0')
		{
			skip = expand_dollar_length(str, pos);
			str = expand_dollar_hd(env, str, pos);
			pos += skip;
		}
		pos++;
	}
	return (str);
}

char	*go_heredoc(char *env[], char *eof, int pipe_count)
{
	int		fd;
	char	*filename;
	char	*str;

	//signals (ctrl+c)
	filename = get_hd_filename(pipe_count);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "Heredoc file creation failed.\n", 30);
		return (NULL);
	}
	str = readline("> ");
	while (str && ft_strcmp(str, eof) != 0)
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
