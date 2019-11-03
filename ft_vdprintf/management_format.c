/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 08:30:43 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:12:12 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

static int	store_fieldwidth(t_vdprintf *store, char *format, va_list ap)
{
	int index;
	int counter;

	index = 0;
	if (format[index] == '*')
	{
		store->field_width = va_arg(ap, int);
		if (store->field_width < 0)
		{
			store->field_width *= -1;
			store->flag_minus = 1;
		}
		index++;
	}
	else
	{
		counter = 0;
		store->field_width = get_number(&format[index], &counter);
		index += counter;
	}
	return (index);
}

static int	store_precision(t_vdprintf *store, char *format, va_list ap)
{
	int index;
	int counter;

	index = 1;
	if (format[index] == '*')
	{
		store->precision = va_arg(ap, int);
		index++;
	}
	else
	{
		counter = 0;
		store->precision = get_number(&format[index], &counter);
		index += counter;
	}
	return (index);
}

static int	store_flags(t_vdprintf *store, char *format)
{
	int index;

	index = 0;
	while (format[index] != '\0' && is_a_flag(format[index]))
	{
		if (format[index] == '+')
			store->flag_plus = 1;
		else if (format[index] == '-')
			store->flag_minus = 1;
		else if (format[index] == '0')
			store->flag_zero = 1;
		else if (format[index] == ' ')
			store->flag_space = 1;
		else if (format[index] == '#')
			store->flag_hashtag = 1;
		index++;
	}
	return (index);
}

static int	store_lengthmodifier(t_vdprintf *store, char *format)
{
	int counter;

	counter = 0;
	if (format[0] == 'h' && format[1] != 'h')
		store->h = 1;
	else if (format[0] == 'h' && format[1] == 'h')
	{
		store->hh = 1;
		counter++;
	}
	else if (format[0] == 'l' && format[1] != 'l')
		store->l = 1;
	else if (format[0] == 'l' && format[1] == 'l')
	{
		store->ll = 1;
		counter++;
	}
	else if (format[0] == 'z')
		store->z = 1;
	else if (format[0] == 'j')
		store->j = 1;
	else if (format[0] == 'L')
		store->longdouble = 1;
	counter++;
	return (counter);
}

int			management_format(t_vdprintf *store, char *format, va_list ap)
{
	int jumper;

	jumper = 0;
	while (format[jumper])
	{
		if (is_a_flag(format[jumper]))
			jumper += store_flags(store, &format[jumper]);
		else if (ft_isdigit(format[jumper]) || format[jumper] == '*')
			jumper += store_fieldwidth(store, &format[jumper], ap);
		else if (format[jumper] == '.')
			jumper += store_precision(store, &format[jumper], ap);
		else if (is_a_lengthmodifier(format[jumper]))
			jumper += store_lengthmodifier(store, &format[jumper]);
		else if (is_a_conversion_character(format[jumper]))
		{
			store->conversion_character = format[jumper++];
			break ;
		}
		else
		{
			store->conversion_character = format[jumper++];
			break ;
		}
	}
	return (jumper);
}
