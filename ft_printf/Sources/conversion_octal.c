/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_octal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:45:31 by hmney             #+#    #+#             */
/*   Updated: 2019/07/06 12:09:44 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen_uintmaxt(t_printf store, const char *number)
{
	int counter;

	counter = (ft_strcmp(number, "0") == 0 && store.precision != 0) ? 1 : 0;
	while (number[counter] != '\0' && ft_strcmp(number, "0") != 0)
		counter++;
	return (counter);
}

static int	calcul_spaces_zeros_uintmaxt(t_printf *store, const char *number)
{
	int length;

	length = ft_strlen_uintmaxt(*store, number);
	store->zeros = store->precision - length;
	if (store->flag_hashtag &&
			(ft_strcmp(number, "0") != 0 || store->precision == 0))
		store->zeros--;
	store->zeros = (store->zeros > 0) ? store->zeros : 0;
	store->spaces = store->field_width - store->zeros - length;
	if (store->flag_hashtag &&
			(ft_strcmp(number, "0") != 0 || store->precision == 0))
		store->spaces--;
	store->spaces = (store->spaces > 0) ? store->spaces : 0;
	return (length + store->spaces + store->zeros + (store->flag_hashtag &&
				(ft_strcmp(number, "0") != 0 || store->precision == 0)));
}

int			conversion_octal(t_printf store, uintmax_t number)
{
	char	*number_string;
	int		counter;

	number_string = ft_itoa_base_uintmaxt(number, 8, 'o');
	counter = calcul_spaces_zeros_uintmaxt(&store, number_string);
	if (!store.flag_minus && !store.flag_zero)
		ft_print_character(store.spaces, ' ');
	if (!store.flag_minus && store.flag_zero && store.precision != -1)
		ft_print_character(store.spaces, ' ');
	if (store.flag_hashtag &&
			(ft_strcmp(number_string, "0") != 0 || store.precision == 0))
		ft_putchar('0');
	if (!store.flag_minus && store.flag_zero && store.precision == -1)
		ft_print_character(store.spaces, '0');
	ft_print_character(store.zeros, '0');
	if (ft_strcmp(number_string, "0") != 0 || store.precision != 0)
		ft_putstr(number_string);
	if (store.flag_minus)
		ft_print_character(store.spaces, ' ');
	free(number_string);
	return (counter);
}
