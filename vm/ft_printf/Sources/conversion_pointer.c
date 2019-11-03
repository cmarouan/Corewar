/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 09:47:28 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:12:12 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

static int	ft_strlen_uintmaxt(t_vdprintf store, const char *number)
{
	int counter;

	counter = (ft_strcmp(number, "0") == 0 && store.precision != 0) ? 1 : 0;
	while (number[counter] != '\0')
		counter++;
	return (counter);
}

static int	calcul_spaces_zeros_uintmaxt(t_vdprintf *store, const char *number)
{
	int length;

	length = ft_strlen_uintmaxt(*store, number);
	store->zeros = store->precision - length;
	store->zeros = (store->zeros > 0) ? store->zeros : 0;
	store->spaces = store->field_width - store->zeros - length - 2;
	store->spaces = (store->spaces > 0) ? store->spaces : 0;
	return (length + store->spaces + store->zeros + 2);
}

int			conversion_pointer(t_vdprintf store, void *ptr)
{
	char	*number_string;
	int		counter;

	number_string = ft_itoa_base_uintmaxt((long)ptr, 16, 'x');
	counter = calcul_spaces_zeros_uintmaxt(&store, number_string);
	if (!store.flag_minus && !store.flag_zero)
		ft_print_character(store.spaces, ' ');
	ft_putstr("0x");
	if (!store.flag_minus && store.flag_zero)
		ft_print_character(store.spaces, '0');
	ft_print_character(store.zeros, '0');
	ft_putstr(number_string);
	if (store.flag_minus)
		ft_print_character(store.spaces, ' ');
	free(number_string);
	return (counter);
}
