/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 13:19:39 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/14 15:34:10 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# include "structs.h"

t_info	*init_info(char *argv[], char *env[]);
void	free_info(t_info *info);

#endif
