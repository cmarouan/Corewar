/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:14:45 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:14:08 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

static int	length_number(t_vdprintf store, uintmax_t number)
{
	int counter;

	counter = (number == 0 && store.precision != 0) ? 1 : 0;
	while (number != 0)
	{
		counter++;
		number /= 10;
	}
	return (counter);
}

static int	calcul_spaces_zeros(t_vdprintf *store, uintmax_t number)
{
	int length;

	length = length_number(*store, number);
	store->zeros = store->precision - length;
	store->zeros = (store->zeros > 0) ? store->zeros : 0;
	store->spaces = store->field_width - store->zeros - length;
	store->spaces = (store->spaces > 0) ? store->spaces : 0;
	return (length + store->spaces + store->zeros);
}

static void	ft_putnbr_intmaxt(t_vdprintf store, uintmax_t number)
{
	if (number >= 10)
		ft_putnbr_intmaxt(store, number / 10);
	ft_putchar_fd(number % 10 + '0', store.fd);
}

int			conversion_unsigned(t_vdprintf store, uintmax_t number)
{
	int counter;

	counter = calcul_spaces_zeros(&store, number);
	if (!store.flag_minus && !store.flag_zero)
		ft_print_character(store, store.spaces, ' ');
	if (!store.flag_minus && store.flag_zero && store.precision != -1)
		ft_print_character(store, store.spaces, ' ');
	if (!store.flag_minus && store.flag_zero && store.precision == -1)
		ft_print_character(store, store.spaces, '0');
	ft_print_character(store, store.zeros, '0');
	if (number != 0 || store.precision != 0)
		ft_putnbr_intmaxt(store, number);
	if (store.flag_minus)
		ft_print_character(store, store.spaces, ' ');
	return (counter);
}
