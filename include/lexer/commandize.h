/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commandize.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 13:26:08 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/25 13:26:31 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDIZE_H
# define COMMANDIZE_H

# include "structs.h"

t_commands	*commandize(t_info *info, char **split);

#endif
