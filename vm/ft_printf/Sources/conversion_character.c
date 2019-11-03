/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_character.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:48:38 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:12:12 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

int		conversion_character(t_vdprintf store, char c)
{
	if (!store.flag_minus)
		ft_print_character(store.field_width - 1, ' ');
	ft_putchar(c);
	if (store.flag_minus)
		ft_print_character(store.field_width - 1, ' ');
	return (store.field_width != 0 ? store.field_width : 1);
}
