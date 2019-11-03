/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_decimal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 10:05:43 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:12:12 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

static int	length_number(t_vdprintf store, intmax_t number)
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

static int	calcul_spaces_zeros(t_vdprintf *store, intmax_t number)
{
	int length;
	int counter;

	length = length_number(*store, number);
	store->zeros = store->precision - length;
	store->zeros = (store->zeros > 0) ? store->zeros : 0;
	store->spaces = store->field_width - store->zeros - length;
	counter = (store->flag_space || store->flag_plus || number < 0);
	store->spaces -= counter;
	store->spaces = (store->spaces > 0) ? store->spaces : 0;
	counter += length + store->spaces + store->zeros;
	return (counter);
}

static void	ft_putnbr_intmaxt(intmax_t number)
{
	uintmax_t n;

	if (number < 0)
		n = number * -1;
	else
		n = number;
	if (n >= 10)
		ft_putnbr_intmaxt(n / 10);
	ft_putchar(n % 10 + '0');
}

int			conversion_decimal(t_vdprintf store, intmax_t number)
{
	int counter;

	counter = calcul_spaces_zeros(&store, number);
	if (!store.flag_minus && !store.flag_zero)
		ft_print_character(store.spaces, ' ');
	if (!store.flag_minus && store.flag_zero && store.precision != -1)
		ft_print_character(store.spaces, ' ');
	if (store.flag_plus)
		(number >= 0) ? ft_putchar('+') : ft_putchar('-');
	if (store.flag_space && !store.flag_plus)
		(number >= 0) ? ft_putchar(' ') : ft_putchar('-');
	if (number < 0 && !store.flag_plus && !store.flag_space)
		ft_putchar('-');
	if (!store.flag_minus && store.flag_zero && store.precision == -1)
		ft_print_character(store.spaces, '0');
	ft_print_character(store.zeros, '0');
	if (number != 0 || store.precision != 0)
		(number >= 0) ? ft_putnbr_intmaxt(number) : ft_putnbr_intmaxt(-number);
	if (store.flag_minus)
		ft_print_character(store.spaces, ' ');
	return (counter);
}
