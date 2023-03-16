/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_add.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 17:44:38 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/03/08 14:18:59 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_ADD_H
# define ENV_ADD_H

int		env_find_var(char *env[], char *var);
char	**env_add(char *env[], char *var, char *value);

#endif
