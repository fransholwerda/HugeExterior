/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/04 13:10:35 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/19 16:13:04 by fholwerd      ########   odam.nl         */
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
#include "signal.h"
#include "stop.h"

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

void	fork_heredoc(char *env[], char *filename, char *eof)
{
	int		fd;
	char	*str;

	redirect_signal(2);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "Heredoc file creation failed.\n", 30);
		exit(EXIT_FAILURE);
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
	free(filename);
	exit(EXIT_SUCCESS);
}

char	*go_heredoc(char *env[], char *eof, int pipe_count)
{
	int		fork_return;
	char	*filename;
	pid_t	pid;

	filename = get_hd_filename(pipe_count);
	redirect_signal(3);
	pid = fork();
	if (pid < 0)
		stop("hd_fork_failure\n");
	else if (pid == 0)
		fork_heredoc(env, filename, eof);
	waitpid(pid, &fork_return, 0);
	redirect_signal(1);
	if (WIFEXITED(fork_return))
		fork_return = WEXITSTATUS(fork_return);
	if (fork_return != 0)
	{
		g_error = fork_return;
		free(filename);
		return (NULL);
	}
	return (filename);
}
