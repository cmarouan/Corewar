/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:33:19 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:14:08 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

int		conversion_string(t_vdprintf store, char *str)
{
	char	*new_string;
	int		spaces;
	int		length;
	int		i;

	if (str == NULL)
		new_string = ft_strdup("(null)");
	else
		new_string = ft_strdup(str);
	length = ft_strlen(new_string);
	if (store.precision != -1)
		length = (length > store.precision) ? store.precision : length;
	spaces = (store.field_width > length) ? store.field_width - length : 0;
	if (!store.flag_minus)
		ft_print_character(store, spaces, ' ');
	i = -1;
	while (*new_string && ++i < length)
		ft_putchar_fd(new_string[i], store.fd);
	if (store.flag_minus)
		ft_print_character(store, spaces, ' ');
	free(new_string);
	return (spaces + length);
}
