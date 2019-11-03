/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 11:45:09 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:12:12 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

static void	multiple_ten(char **number)
{
	char	*result;
	char	*tmp;
	int		length;
	int		index;

	if (ft_strcmp(*number, "0") != 0)
	{
		length = ft_strlen(*number) + 1;
		if (!(result = ft_strnew(length)))
			return ;
		index = -1;
		while (++index < length - 1)
			result[index] = (*number)[index];
		result[index] = '0';
		tmp = *number;
		*number = result;
		free(tmp);
	}
}

static char	*calcul_mantissa(t_vdprintf store, t_float *float_data)
{
	char	*power_five;
	char	*tmp;
	int		index;

	if (store.longdouble && (float_data->integer_part == 0
				|| extendedprecision.float_number == 0.0))
		float_data->mantissa = ft_strdup("0");
	else if (!store.longdouble && singleprecision.float_number == 0.0)
		float_data->mantissa = ft_strdup("0");
	else
		float_data->mantissa = ft_strdup("1");
	index = -1;
	while (float_data->mantissa_binary[++index] != '\0')
	{
		multiple_ten(&float_data->mantissa);
		if (float_data->mantissa_binary[index] == '1')
		{
			tmp = float_data->mantissa;
			power_five = ft_exponent(5, index + 1);
			float_data->mantissa = ft_addition(tmp, power_five);
			free(power_five);
			free(tmp);
		}
	}
	return (float_data->mantissa);
}

static char	*calcul_exponent(t_float *float_data)
{
	char	*exponent;
	int		base;
	int		number;

	number = float_data->exponent_number - float_data->bias;
	if (number >= 0)
	{
		base = 2;
		float_data->comma++;
		exponent = ft_exponent(base, number);
	}
	else
	{
		float_data->comma += number + 1;
		base = 5;
		exponent = ft_exponent(base, ABS(number));
	}
	return (exponent);
}

static char	*calcul_mantissa_binary(t_vdprintf store, t_float float_data)
{
	char *result;

	if (store.longdouble)
		result = convert_binary(float_data.mantissa_number, 63);
	else
		result = convert_binary(float_data.mantissa_number, 52);
	return (result);
}

char		*calcul_float(t_vdprintf *store, t_float *float_data)
{
	char	*data;
	char	*tmp;
	int		length_final;
	int		length_data;

	float_data->mantissa_binary = calcul_mantissa_binary(*store, *float_data);
	float_data->mantissa = calcul_mantissa(*store, float_data);
	float_data->exponent = calcul_exponent(float_data);
	data = ft_multiple(float_data->mantissa, float_data->exponent);
	length_data = ft_strlen(data);
	float_data->comma += length_data - ft_strlen(float_data->mantissa);
	length_final = length_float(store, float_data, length_data);
	if (length_final > length_data)
	{
		tmp = data;
		data = add_zeros(*float_data, data, length_data, length_final);
		if (float_data->comma <= 0)
			float_data->comma = 1;
		free(tmp);
	}
	return (data);
}
