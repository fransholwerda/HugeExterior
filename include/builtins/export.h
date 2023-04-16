/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 17:52:59 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/16 16:11:28 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "structs.h"

char	**export(char *env[], char *args[], int fd);
char	**export_var(char *env[], char *var);

#endif
