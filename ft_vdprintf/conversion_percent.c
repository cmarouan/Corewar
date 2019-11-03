/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 00:26:21 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:14:08 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

int	conversion_percent(t_vdprintf store)
{
	if (!store.flag_minus && !store.flag_zero)
		ft_print_character(store, store.field_width - 1, ' ');
	if (!store.flag_minus && store.flag_zero)
		ft_print_character(store, store.field_width - 1, '0');
	ft_putchar_fd('%', store.fd);
	if (store.flag_minus)
		ft_print_character(store, store.field_width - 1, ' ');
	return (store.field_width ? store.field_width : 1);
}
