/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/28 16:17:07 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/26 18:31:23 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>

typedef struct s_file
{
	char			*name;
	int				mode;
	int				mode2; //-1 if not, else use it
	struct s_file	*next;
}					t_file;

typedef struct s_commands
{
	char				**args;
	t_file				*infile;
	t_file				*outfile;
	char				*hd;
	struct s_commands	*next;
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
