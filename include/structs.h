/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/28 16:17:07 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/20 14:52:11 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <unistd.h>

typedef struct s_three_ints
{
	int	start;
	int	end;
	int	i;
}		t_three_ints;

typedef struct s_file
{
	char			*name;
	int				mode;
	int				mode2; //-1 if not, else use it
	bool			hd;
	struct s_file	*next;
}					t_file;

typedef struct s_commands
{
	char				**args;
	t_file				*infile;
	t_file				*outfile;
	struct s_commands	*next;
	struct s_commands	*prev;
}						t_commands;

typedef struct s_metainfo
{
	char	**envp;
	pid_t	lastpid;
	int		infilefd;
	int		outfilefd;
	char	*path;
}			t_metainfo;

typedef struct s_info
{
	char		*prompt;
	char		**env;
	t_commands	*cmds;
}	t_info;

#endif
