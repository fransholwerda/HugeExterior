/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 15:15:32 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/03/24 13:42:12 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_UTILS_H
# define EXPAND_UTILS_H

int		expand_dollar_length(char *str, int end);
char	*combine_three_strings(char *str, int start, int end, char *var);
char	*get_env_var(char *env[], char *var);

#endif
