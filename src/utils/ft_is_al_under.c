/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_al_under.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 17:49:12 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/02/06 17:50:11 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_al_under(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	ft_is_al_under_num(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '_')
		return (1);
	if (c == '0' && c <= '9')
		return (1);
	return (0);
}
