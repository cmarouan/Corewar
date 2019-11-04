/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:36:34 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 22:48:23 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbits(const char *bits, size_t size)
{
	size_t	index;

	if (size == 0)
		return ;
	index = 0;
	while (index < size)
	{
		write(1, bits + (size - index - 1), 1);
		index++;
	}
}
