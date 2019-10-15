/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 08:16:03 by hmney             #+#    #+#             */
/*   Updated: 2019/07/01 08:16:08 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*convert_binary(unsigned long mantissa_number, int length)
{
	char	*mantissa_binary;

	if (!(mantissa_binary = ft_strnew(length)))
		return (NULL);
	while (length && mantissa_number != 0)
	{
		mantissa_binary[--length] = (mantissa_number % 2) + '0';
		mantissa_number /= 2;
	}
	while (length)
		mantissa_binary[--length] = '0';
	return (mantissa_binary);
}
