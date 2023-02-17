/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 21:16:24 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/17 19:20:50 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>
# include <unistd.h>
# include "structs.h"

bool	check_builtin(t_commands *commands);
int		execute_builtin(t_commands *commands, t_metainfo *info);

#endif