/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 00:26:21 by hmney             #+#    #+#             */
/*   Updated: 2019/07/01 08:14:48 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conversion_percent(t_printf store)
{
	if (!store.flag_minus && !store.flag_zero)
		ft_print_character(store.field_width - 1, ' ');
	if (!store.flag_minus && store.flag_zero)
		ft_print_character(store.field_width - 1, '0');
	ft_putchar('%');
	if (store.flag_minus)
		ft_print_character(store.field_width - 1, ' ');
	return (store.field_width ? store.field_width : 1);
}
