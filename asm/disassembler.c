/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:51:54 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 21:18:01 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	read_arg_type(int args[], int op_code, int fd_read, int fd_write)
{
	int index;
	int shift;
	int arg_type;

	arg_type = 0;
	if (read(fd_read, &arg_type, 1) < 0)
		return (0);
	index = -1;
	shift = 6;
	while (++index < g_op_tab[op_code - 1].number_registries)
	{
		args[index] = arg_type >> shift;
		arg_type ^= args[index] << shift;
		shift -= 2;
	}
	return (1);
}

static int	read_args(int args[], int op_code, int fd_read, int fd_write)
{
	int index;

	index = -1;
	while (++index < g_op_tab[op_code - 1].number_registries)
	{
		if (args[index] & REG_CODE)
		{
			if (!read_arg_reg(op_code, fd_read, fd_write))
				return (0);
		}
		else if (args[index] & DIR_CODE)
		{
			if (!read_arg_dir(op_code, fd_read, fd_write))
				return (0);
		}
		else if (args[index] & IND_CODE)
		{
			if (!read_arg_ind(fd_read, fd_write))
				return (0);
		}
		if (index + 1 != g_op_tab[op_code - 1].number_registries)
			ft_dprintf(fd_write, ", ");
	}
	return (1);
}

int			read_header(t_header header, int fd_read, int fd_write)
{
	int bytes;

	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0 ||
			ft_swap_int32(bytes) != COREWAR_EXEC_MAGIC)
		return (0);
	if (read(fd_read, header.prog_name, PROG_NAME_LENGTH) < 0)
		return (0);
	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0 || bytes)
		return (0);
	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0)
		return (0);
	header.prog_size = bytes;
	if (read(fd_read, header.comment, COMMENT_LENGTH) < 0)
		return (0);
	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0 || bytes)
		return (0);
	ft_dprintf(fd_write, "%s \"%s\"\n", NAME_CMD_STRING, header.prog_name);
	ft_dprintf(fd_write, "%s \"%s\"\n\n", COMMENT_CMD_STRING, header.comment);
	return (1);
}

int			read_assembly_code(int fd_read, int fd_write)
{
	int op_code;
	int	args[3];
	int index;

	op_code = 0;
	ft_bzero((void *)&args, sizeof(int) * 3);
	while (read(fd_read, &op_code, 1) > 0)
	{
		index = -1;
		if (op_code < 1 || op_code > 16)
			return (0);
		ft_dprintf(fd_write, "%s ", g_op_tab[op_code - 1].instruction);
		if (!g_op_tab[op_code - 1].argument_type_code)
			while (++index < 3)
				args[index] = g_op_tab[op_code - 1].type_argument[index];
		else if (!read_arg_type(args, op_code, fd_read, fd_write))
			return (0);
		if (!read_args(args, op_code, fd_read, fd_write))
			return (0);
		ft_dprintf(fd_write, "\n");
	}
	return (1);
}
