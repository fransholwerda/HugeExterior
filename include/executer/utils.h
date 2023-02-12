/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 22:29:15 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/12 22:30:51 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>

size_t	ft_strlen(const char *str);
void	ft_putendl_fd(char *string, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *str1, const char *str2, size_t size);
void	ft_putstr_fd(char *string, int fd);

#endif