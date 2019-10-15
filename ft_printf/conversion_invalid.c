/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_invalid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:00:34 by hmney             #+#    #+#             */
/*   Updated: 2019/07/11 18:00:37 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conversion_invalid(t_printf store, char conversion_character)
{
	if (!store.flag_minus && !store.flag_zero)
		ft_print_character(store.field_width - 1, ' ');
	if (!store.flag_minus && store.flag_zero)
		ft_print_character(store.field_width - 1, '0');
	ft_putchar(conversion_character);
	if (store.flag_minus)
		ft_print_character(store.field_width - 1, ' ');
	return (store.field_width ? store.field_width : 1);
}
