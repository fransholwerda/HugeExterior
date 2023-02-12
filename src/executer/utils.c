/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 06:41:37 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/12 22:30:59 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putendl_fd(char *string, int fd)
{
	int	len;

	len = ft_strlen(string);
	if (fd >= 0 && string != NULL)
	{
		write(fd, string, len);
		write(fd, "\n", 1);
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fullstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	fullstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (fullstr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		fullstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		fullstr[i + j] = s2[j];
		j++;
	}
	fullstr[i + j] = '\0';
	return (fullstr);
}

int		ft_strncmp(const char *str1, const char *str2, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (0);
	while (str1[i] != '\0' && i < (size - 1) && str1[i] == str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

void	ft_putstr_fd(char *string, int fd)
{
	int	len;

	len = ft_strlen(string);
	if (fd >= 0 && string != NULL)
		write(fd, string, len);
}


