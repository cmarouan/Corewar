/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_length_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 11:52:12 by hmney             #+#    #+#             */
/*   Updated: 2019/07/18 11:52:45 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_length_number(intmax_t number)
{
	int length;

	length = (number == 0) ? 1 : 0;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}
