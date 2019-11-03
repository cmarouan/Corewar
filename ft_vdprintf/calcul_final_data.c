/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_final_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 11:41:21 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:14:08 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

static int	is_even(char *number)
{
	int length;
	int num;

	length = ft_strlen(number);
	num = number[length - 1] - '0';
	if (num % 2 == 0)
		return (1);
	else
		return (0);
}

static int	rounding_updown(char *number1, char *number2)
{
	int num;
	int index;

	num = number1[0] - '0';
	if (num < 5)
		return (0);
	else if (num > 5)
		return (1);
	else
	{
		index = 0;
		while (number1[++index])
		{
			if (number1[index] != '0')
				return (1);
		}
		return (is_even(number2) ? 0 : 1);
	}
}

static char	*put_comma(char *number, int comma)
{
	char	*result;
	int		length;
	int		index;
	int		index2;

	length = ft_strlen(number) + 1;
	if (!(result = ft_strnew(length)))
		return (NULL);
	index = -1;
	index2 = -1;
	while (++index2 < length)
	{
		if (index2 == comma)
		{
			result[index2] = '.';
			continue;
		}
		result[index2] = number[++index];
	}
	return (result);
}

char		*calcul_final_data(t_vdprintf store, t_float *float_data)
{
	char	*result;
	char	*tmp;
	int		position;

	float_data->data = calcul_float(&store, float_data);
	position = float_data->comma;
	position += (store.precision >= 0) ? store.precision : 6;
	result = ft_strsub(float_data->data, 0, position);
	if (rounding_updown(float_data->data + position, result))
	{
		tmp = result;
		result = ft_addition("1", result);
		float_data->comma += (ft_strlen(result) > ft_strlen(tmp)) ? 1 : 0;
		free(tmp);
	}
	if (store.precision != 0)
	{
		tmp = result;
		result = put_comma(result, float_data->comma);
		free(tmp);
	}
	return (result);
}
