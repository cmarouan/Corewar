/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 13:17:43 by hmney             #+#    #+#             */
/*   Updated: 2019/07/24 13:18:22 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *str)
{
	size_t index;

	index = 0;
	if (str[index] == '\0')
		return (0);
	if ((str[index] == '+' || str[index] == '-') && str[index + 1] != '\0')
		index++;
	while (str[index] != '\0')
	{
		if (!ft_isdigit(str[index]))
			return (0);
		index++;
	}
	return (1);
}
