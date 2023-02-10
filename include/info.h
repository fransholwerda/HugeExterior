/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 13:19:39 by fholwerd      #+#    #+#                 */
/*   Updated: 2022/11/26 17:33:47 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# include "structs.h"

t_info	*init_info(char *argv[]);
void	free_info(t_info *info);

#endif
