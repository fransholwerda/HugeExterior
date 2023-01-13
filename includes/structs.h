/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/28 16:17:07 by ahorling      #+#    #+#                 */
/*   Updated: 2023/01/13 20:54:30 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_file
{
    char			*file;
    int				mode;
    struct s_file	*next;
}                    t_file;


typedef struct s_commands
{
    char				**list_of_commands;
    t_file				infile;
    t_file				outfile;
    int         		hd_pipe[2];
    struct s_commands	*next;
}						t_commands;

typedef struct s_metainfo
{
    char    **envp;
    pid_t   lastpid;
}           t_metainfo;

#endif


path = true                         false
list of commands [0] = path         list of commands [0] = ls
list of commands [1] = ls           list of commands [1] = -a
list of commands [2] = -a           list of commands [2] 
list of commands [3] 