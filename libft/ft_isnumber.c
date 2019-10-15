/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 13:17:43 by hmney             #+#    #+#             */
/*   Updated: 2019/10/15 19:00:37 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *str)
{
	size_t index;

	index = 0;
	while (str[index] != '\0')
	{
		if (!ft_isdigit(str[index]))
			return (0);
		index++;
	}
	return (index != 0);
}
