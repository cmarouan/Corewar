/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 23:23:43 by hmney             #+#    #+#             */
/*   Updated: 2018/10/11 15:33:51 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_allocation(int n)
{
	int counter;

	counter = 0;
	if (n <= 0)
		counter++;
	while (n != 0)
	{
		counter++;
		n = n / 10;
	}
	return (counter);
}

char		*ft_itoa(int n)
{
	char		*str;
	int			i;
	int			taille;
	long long	nb;

	nb = (long long)n;
	taille = ft_allocation(nb);
	if ((str = (char *)malloc(sizeof(char) * (taille + 1))) == NULL)
		return (NULL);
	i = 0;
	if (nb < 0)
	{
		nb *= -1;
		*str = '-';
		i = 1;
	}
	*(str + taille) = '\0';
	while (taille != i)
	{
		*(str + taille - 1) = nb % 10 + '0';
		nb = nb / 10;
		taille--;
	}
	return (str);
}
