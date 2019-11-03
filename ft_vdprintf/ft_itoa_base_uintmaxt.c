/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_uintmaxt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 22:37:13 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:14:08 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

static int	ft_allocation(uintmax_t number, int base)
{
	int counter;

	counter = (number == 0) ? 1 : 0;
	while (number != 0)
	{
		counter++;
		number /= base;
	}
	return (counter);
}

char		*ft_itoa_base_uintmaxt(uintmax_t number, int base, char c)
{
	char	*str;
	int		taille;
	char	*base_string;

	if (c == 'X')
		base_string = ft_strdup("0123456789ABCDEF");
	if (c == 'x')
		base_string = ft_strdup("0123456789abcdef");
	if (c == 'o')
		base_string = ft_strdup("01234567");
	if (c == 'b' || c == 'B')
		base_string = ft_strdup("01");
	taille = ft_allocation(number, base);
	if ((str = (char *)malloc(sizeof(char) * (taille + 1))) == NULL)
		return (NULL);
	str[taille] = '\0';
	while (taille--)
	{
		str[taille] = base_string[number % base];
		number /= base;
	}
	free(base_string);
	return (str);
}
