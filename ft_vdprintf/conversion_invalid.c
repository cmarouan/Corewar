/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_invalid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:00:34 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:14:08 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

int	conversion_invalid(t_vdprintf store, char conversion_character)
{
	if (!store.flag_minus && !store.flag_zero)
		ft_print_character(store, store.field_width - 1, ' ');
	if (!store.flag_minus && store.flag_zero)
		ft_print_character(store, store.field_width - 1, '0');
	ft_putchar_fd(conversion_character, store.fd);
	if (store.flag_minus)
		ft_print_character(store, store.field_width - 1, ' ');
	return (store.field_width ? store.field_width : 1);
}
