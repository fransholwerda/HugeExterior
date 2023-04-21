/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   separate_cmds.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 17:13:56 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/06 18:05:51 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATE_CMDS_H
# define SEPARATE_CMDS_H

int		skip_until(char *str, int pos, char c);
char	**separate_cmds(char **split);

#endif
