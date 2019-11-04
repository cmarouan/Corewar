/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_disassembler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:48:29 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 22:57:08 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	read_arg_reg(int fd_read, int fd_write)
{
	int bytes;

	bytes = 0;
	if (read(fd_read, &bytes, 1) < 0)
		return (0);
	ft_dprintf(fd_write, "r%d", bytes);
	return (1);
}

int	read_arg_dir(int op_code, int fd_read, int fd_write)
{
	int bytes;
	int nb_byte;

	bytes = 0;
	nb_byte = (g_op_tab[op_code - 1].changes_carry ? 2 : 4);
	if (read(fd_read, &bytes, nb_byte) < 0)
		return (0);
	if (nb_byte == 2)
		ft_dprintf(fd_write, "%%%d", ft_swap_int16((int16_t)bytes));
	else
		ft_dprintf(fd_write, "%%%d", ft_swap_int32((int32_t)bytes));
	return (1);
}

int	read_arg_ind(int fd_read, int fd_write)
{
	int bytes;

	bytes = 0;
	if (read(fd_read, &bytes, 2) < 0)
		return (0);
	ft_dprintf(fd_write, "%d", ft_swap_int16((int16_t)bytes));
	return (1);
}
