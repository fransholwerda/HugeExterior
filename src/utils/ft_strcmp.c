/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 15:04:34 by ahorling      #+#    #+#                 */
/*   Updated: 2023/02/17 19:15:19 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char const *string1, char const *string2)
{
	int	i;

	i = 0;
	while (string1[i] != '\0')
	{
		if (string1[i] - string2[i] == 0)
			i++;
		else
			return (string1[i] - string2[i]);
	}
	if (string2[i] != '\0')
		return (string2[i]);
	else
		return (0);
}
