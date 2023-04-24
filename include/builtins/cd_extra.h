/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_extra.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 21:53:41 by ahorling      #+#    #+#                 */
/*   Updated: 2023/04/24 21:59:45 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_EXTRA_H
# define CD_EXTRA_H

# include "structs.h"

void	cd_to_non_home(t_metainfo *info, char *buffer, char *oldpwd, char *pwd);

#endif