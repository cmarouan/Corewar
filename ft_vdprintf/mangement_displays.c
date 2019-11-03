/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mangement_displays.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 07:59:33 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:14:08 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

void	management_display_u(va_list ap, t_vdprintf *store)
{
	if (store->l)
		store->length_result += conversion_unsigned(*store, va_arg(ap, long));
	else if (store->ll)
		store->length_result += conversion_unsigned(*store,
				va_arg(ap, long long));
	else if (store->z)
		store->length_result += conversion_unsigned(*store,
				va_arg(ap, size_t));
	else if (store->h)
		store->length_result += conversion_unsigned(*store,
				(unsigned short)va_arg(ap, int));
	else if (store->hh)
		store->length_result += conversion_unsigned(*store,
				(unsigned char)va_arg(ap, int));
	else
		store->length_result += conversion_unsigned(*store,
				(unsigned)va_arg(ap, int));
}

void	management_display_o(va_list ap, t_vdprintf *store)
{
	if (store->l)
		store->length_result += conversion_octal(*store, va_arg(ap, long));
	else if (store->ll)
		store->length_result += conversion_octal(*store, va_arg(ap, long long));
	else if (store->z)
		store->length_result += conversion_octal(*store, va_arg(ap, size_t));
	else if (store->j)
		store->length_result += conversion_octal(*store, va_arg(ap, uintmax_t));
	else if (store->h)
		store->length_result += conversion_octal(*store,
				(unsigned short)va_arg(ap, int));
	else if (store->hh)
		store->length_result += conversion_octal(*store,
				(unsigned char)va_arg(ap, int));
	else
		store->length_result += conversion_octal(*store,
				(unsigned)va_arg(ap, int));
}

void	management_display_d(va_list ap, t_vdprintf *store)
{
	if (store->l)
		store->length_result += conversion_decimal(*store,
				(long)va_arg(ap, long));
	else if (store->ll)
		store->length_result += conversion_decimal(*store,
				(long long)va_arg(ap, long long));
	else if (store->h)
		store->length_result += conversion_decimal(*store,
				(short)va_arg(ap, int));
	else if (store->hh)
		store->length_result += conversion_decimal(*store,
				(char)va_arg(ap, int));
	else
		store->length_result += conversion_decimal(*store, va_arg(ap, int));
}

void	management_display_x(va_list ap, t_vdprintf *store)
{
	char c;

	c = store->conversion_character;
	if (store->l)
		store->length_result += conversion_hexadecimal(*store,
				va_arg(ap, long), c);
	else if (store->ll)
		store->length_result += conversion_hexadecimal(*store,
				va_arg(ap, long long), c);
	else if (store->z)
		store->length_result += conversion_hexadecimal(*store,
				va_arg(ap, size_t), c);
	else if (store->j)
		store->length_result += conversion_hexadecimal(*store,
				va_arg(ap, uintmax_t), c);
	else if (store->h)
		store->length_result += conversion_hexadecimal(*store,
				(unsigned short)va_arg(ap, int), c);
	else if (store->hh)
		store->length_result += conversion_hexadecimal(*store,
				(unsigned char)va_arg(ap, int), c);
	else
		store->length_result += conversion_hexadecimal(*store,
				(unsigned)va_arg(ap, int), c);
}

void	management_display_f(va_list ap, t_vdprintf *store)
{
	if (store->longdouble)
		store->length_result += conversion_float(*store,
				va_arg(ap, long double));
	else
		store->length_result += conversion_float(*store,
				(double)va_arg(ap, double));
}
