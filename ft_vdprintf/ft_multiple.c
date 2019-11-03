/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 08:21:56 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:12:11 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

static	char	*mul(char *number1, int number2, int length, int step)
{
	char	*result;
	int		tmp;
	int		rest;
	int		index;

	index = length + step + 1;
	if (!(result = ft_strnew(index)))
		return (NULL);
	rest = 0;
	while (step--)
		result[--index] = '0';
	while (index--)
	{
		rest = (rest == 0 && length == 0) ? '-' - '0' : rest;
		tmp = (length) ? ((number1[--length] - '0') * number2) + rest : rest;
		if (tmp >= 10)
		{
			rest = tmp / 10;
			tmp %= 10;
		}
		else
			rest = 0;
		result[index] = tmp + '0';
	}
	return (result);
}

char			*ft_multiple(char *number1, char *number2)
{
	char	*result;
	char	*copy_number1;
	char	*copy_number2;
	int		index;
	int		step;

	result = ft_strdup("0");
	index = ft_strlen(number2);
	step = 0;
	while (index--)
	{
		copy_number1 = result;
		copy_number2 = mul(number1, number2[index] - '0', ft_strlen(number1),
				step++);
		delete_empty_space(&copy_number2);
		result = ft_addition(copy_number1, copy_number2);
		free(copy_number1);
		free(copy_number2);
	}
	return (result);
}
