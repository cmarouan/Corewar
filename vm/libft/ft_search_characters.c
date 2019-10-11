/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_characters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 14:37:26 by hmney             #+#    #+#             */
/*   Updated: 2019/07/29 14:46:47 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_search_characters(char *str, char search)
{
	size_t	index;
	int		counter;

	index = -1;
	counter = 0;
	while (str[++index] != '\0')
	{
		if (str[index] == search)
			counter++;
	}
	return (counter);
}
