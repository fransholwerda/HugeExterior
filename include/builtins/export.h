/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 17:52:59 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/04/20 17:06:27 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "structs.h"

int		find_char(char *str, char c);
char	**export(char *env[], char *args[], int fd);
char	**export_var(char *env[], char *var);

#endif
