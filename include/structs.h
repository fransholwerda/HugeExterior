/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/28 16:17:07 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/10 17:58:57 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>

typedef struct s_file
{
	char			*file; //rename to name
	int				mode;
	struct s_file	*next;
}					t_file;

typedef struct s_commands
{
	char				**list_of_commands; //rename to args
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
	t_commands	*cmds;
}	t_info;

#endif
