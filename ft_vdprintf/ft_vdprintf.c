/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:35:44 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 22:35:59 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

static void	management_display_cap(va_list ap, t_vdprintf *store)
{
	if (store->conversion_character == 'C')
		store->length_result += conversion_character(*store, va_arg(ap, int));
	else if (store->conversion_character == 'S')
		store->length_result += conversion_string(*store, va_arg(ap, char *));
	else if (store->conversion_character == 'P')
		store->length_result += conversion_pointer(*store, va_arg(ap, void *));
	else if (store->conversion_character == 'D' ||
			store->conversion_character == 'I')
		management_display_d(ap, store);
	else if (store->conversion_character == 'O')
		management_display_o(ap, store);
	else if (store->conversion_character == 'U')
		management_display_u(ap, store);
	else if (store->conversion_character == '%')
		store->length_result += conversion_percent(*store);
	else if (store->conversion_character != '0')
		store->length_result += conversion_invalid(*store,
		store->conversion_character);
}

static void	management_display(va_list ap, t_vdprintf *store)
{
	if (store->conversion_character == 'c')
		store->length_result += conversion_character(*store, va_arg(ap, int));
	else if (store->conversion_character == 's')
		store->length_result += conversion_string(*store, va_arg(ap, char *));
	else if (store->conversion_character == 'p')
		store->length_result += conversion_pointer(*store, va_arg(ap, void *));
	else if (store->conversion_character == 'd' ||
			store->conversion_character == 'i')
		management_display_d(ap, store);
	else if (store->conversion_character == 'o')
		management_display_o(ap, store);
	else if (store->conversion_character == 'u')
		management_display_u(ap, store);
	else if (store->conversion_character == 'x' ||
			store->conversion_character == 'X')
		management_display_x(ap, store);
	else if (store->conversion_character == 'f' ||
			store->conversion_character == 'F')
		management_display_f(ap, store);
	else if (store->conversion_character == 'b' ||
			store->conversion_character == 'B')
		store->length_result += conversion_binary(*store, va_arg(ap, int),
		store->conversion_character);
	else
		management_display_cap(ap, store);
}

static void	init_struct(t_vdprintf *new)
{
	new->flag_plus = 0;
	new->flag_minus = 0;
	new->flag_zero = 0;
	new->flag_space = 0;
	new->flag_hashtag = 0;
	new->h = 0;
	new->hh = 0;
	new->l = 0;
	new->ll = 0;
	new->z = 0;
	new->j = 0;
	new->longdouble = 0;
	new->field_width = 0;
	new->precision = -1;
	new->conversion_character = '0';
	new->spaces = 0;
	new->zeros = 0;
}

int			ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_vdprintf	store;

	store.length_result = 0;
	store.fd = fd;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			init_struct(&store);
			format += management_format(&store, (char*)format, ap);
			management_display(ap, &store);
		}
		else
		{
			ft_putchar_fd(*format, store.fd);
			store.length_result++;
			format++;
		}
	}
	return (store.length_result);
}
