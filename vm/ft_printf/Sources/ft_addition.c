/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 08:16:43 by hmney             #+#    #+#             */
/*   Updated: 2019/07/08 14:52:57 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		add(char number1, char number2, int *rest)
{
	int result;

	result = *rest + (number1 - '0') + (number2 - '0');
	if (result >= 10)
	{
		*rest = result / 10;
		result -= 10;
	}
	else
		*rest = 0;
	return (result + '0');
}

static int		max_number(char *number1, char *number2)
{
	int length1;
	int length2;

	length1 = ft_strlen(number1);
	length2 = ft_strlen(number2);
	return ((length1 >= length2) ? length1 : length2);
}

char			*ft_addition(char *number1, char *number2)
{
	char	*result;
	int		length1;
	int		length2;
	int		reste;
	int		max;

	max = max_number(number1, number2) + 1;
	if (!(result = ft_strnew(max)))
		return (NULL);
	length1 = ft_strlen(number1);
	length2 = ft_strlen(number2);
	reste = 0;
	while (max--)
	{
		if (length1 != 0 && length2 != 0)
			result[max] = add(number1[--length1], number2[--length2], &reste);
		else if (length1 == 0 && length2)
			result[max] = add('0', number2[--length2], &reste);
		else if (length2 == 0 && length1)
			result[max] = add(number1[--length1], '0', &reste);
		else if (length1 == 0 && length2 == 0)
			result[max] = (reste > 0) ? reste + '0' : '-';
	}
	delete_empty_space(&result);
	return (result);
}
