/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 15:04:06 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:14:08 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

static void	init_float(t_vdprintf store, t_float *float_data, long double number)
{
	if (store.longdouble)
	{
		extendedprecision.float_number = number;
		float_data->mantissa_number = extendedprecision.data.mantissa;
		float_data->exponent_number = extendedprecision.data.exponent;
		float_data->sign = extendedprecision.data.sign;
		float_data->integer_part = extendedprecision.data.integer_part;
		float_data->bias = 16383;
		float_data->comma = 0;
	}
	else
	{
		singleprecision.float_number = number;
		float_data->mantissa_number = singleprecision.data.mantissa;
		float_data->exponent_number = singleprecision.data.exponent;
		float_data->sign = singleprecision.data.sign;
		float_data->integer_part = 1;
		float_data->bias = 1023;
		float_data->comma = 0;
	}
}

static void	free_float_data(t_float *float_data)
{
	free(float_data->data);
	free(float_data->final_data);
	free(float_data->mantissa_binary);
	free(float_data->mantissa);
	free(float_data->exponent);
}

static int	calcul_spaces(t_vdprintf *store, t_float float_data)
{
	int counter;

	counter = ft_strlen(float_data.final_data);
	if (float_data.exponent_number == EL ||
			float_data.exponent_number == ED)
		counter += ((store->flag_space || store->flag_plus || float_data.sign)
				&& !float_data.mantissa_number);
	else
	{
		counter += (store->flag_hashtag && store->precision == 0);
		counter += (store->flag_space || store->flag_plus || float_data.sign);
	}
	store->spaces = store->field_width - ft_strlen(float_data.final_data);
	store->spaces = (store->spaces > 0) ? store->spaces : 0;
	if (float_data.mantissa_number && (float_data.exponent_number == EL ||
				float_data.exponent_number == ED))
		return (store->spaces + counter);
	store->spaces -= store->flag_plus;
	store->spaces -= (store->flag_space && !store->flag_plus);
	store->spaces -= (float_data.sign && !store->flag_plus &&
			!store->flag_space);
	store->spaces = (store->spaces > 0) ? store->spaces : 0;
	return (store->spaces + counter);
}

static int	special_case(t_vdprintf store, t_float *float_data)
{
	int counter;

	float_data->data = calcul_float(&store, float_data);
	float_data->final_data = calcul_fd_specialcase(store, *float_data);
	counter = calcul_spaces(&store, *float_data);
	if (!store.flag_minus)
		ft_print_character(store, store.spaces, ' ');
	if ((store.flag_space || store.flag_plus || float_data->sign)
	&& !float_data->mantissa_number)
	{
		if (store.flag_plus)
			(!float_data->sign) ? ft_putchar_fd('+', store.fd) :
				ft_putchar_fd('-', store.fd);
		if (store.flag_space && !store.flag_plus)
			(!float_data->sign) ? ft_putchar_fd(' ', store.fd) :
				ft_putchar_fd('-', store.fd);
		if (float_data->sign && !store.flag_plus && !store.flag_space)
			ft_putchar_fd('-', store.fd);
	}
	ft_putstr_fd(float_data->final_data, store.fd);
	if (store.flag_minus)
		ft_print_character(store, store.spaces, ' ');
	free_float_data(float_data);
	return (counter);
}

int			conversion_float(t_vdprintf store, long double number)
{
	t_float float_data;
	int		counter;

	init_float(store, &float_data, number);
	if (float_data.exponent_number == EL || float_data.exponent_number == ED)
		return (special_case(store, &float_data));
	float_data.final_data = calcul_final_data(store, &float_data);
	counter = calcul_spaces(&store, float_data);
	if (!store.flag_minus && !store.flag_zero)
		ft_print_character(store, store.spaces, ' ');
	if (store.flag_plus)
		(!float_data.sign) ? ft_putchar_fd('+', store.fd) : ft_putchar_fd('-', store.fd);
	if (store.flag_space && !store.flag_plus)
		(!float_data.sign) ? ft_putchar_fd(' ', store.fd) : ft_putchar_fd('-', store.fd);
	if (float_data.sign && !store.flag_plus && !store.flag_space)
		ft_putchar_fd('-', store.fd);
	if (!store.flag_minus && store.flag_zero)
		ft_print_character(store, store.spaces, '0');
	ft_putstr_fd(float_data.final_data, store.fd);
	if (store.flag_hashtag && store.precision == 0)
		ft_putchar_fd('.', store.fd);
	if (store.flag_minus)
		ft_print_character(store, store.spaces, ' ');
	free_float_data(&float_data);
	return (counter);
}
