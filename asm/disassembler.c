/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:51:54 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:34:16 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int create_header(t_header header, int fd_read, int fd_write)
{
	int bytes;
	
	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0 || ft_swap_int32(bytes) != COREWAR_EXEC_MAGIC)
		return (0);
	if (read(fd_read, header.prog_name, PROG_NAME_LENGTH) < 0)
		return (0);
	ft_dprintf(fd_write, "%s \"%s\"\n", NAME_CMD_STRING, header.prog_name);
	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0)
		return (0);
	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0)
		return (0);
	if (read(fd_read, header.comment, COMMENT_LENGTH) < 0)
		return (0);
	ft_dprintf(fd_write, "%s \"%s\"\n\n",COMMENT_CMD_STRING, header.comment);
	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0)
		return (0);
	return (1);
}

int create_assembly_code(int fd_read, int fd_write)
{
	int op_code;
	int arg_type;
	int	args[3];
	int index;
	int shift;
	unsigned int value;

	op_code = 0;
	ft_bzero((void *)&args, sizeof(int) * 3);
	while (read(fd_read, &op_code, 1) > 0)
	{
		if (op_code < 1 || op_code > 16)
			return (0);
		ft_dprintf(fd_write, "%s ", g_op_tab[op_code - 1].instruction);
		arg_type = 0;
		if (g_op_tab[op_code - 1].argument_type_code)
		{
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
			index = -1;
			while (++index < g_op_tab[op_code - 1].number_registries)
			{
				value = 0;
				if (args[index] == 0)
					break ;
				if (args[index] & REG_CODE)
				{
					if (read(fd_read, &value, 1) < 0)
						return (0);
					ft_dprintf(fd_write, "r%d", value);
					if (index + 1 != g_op_tab[op_code - 1].number_registries)
						ft_dprintf(fd_write, ", ");
				}
				else if (args[index] & DIR_CODE)
				{
					int byte = (g_op_tab[op_code - 1].changes_carry ? 2 : 4);
					if (read(fd_read, &value, byte) < 0)
						return (0);
					if (byte == 2)
						ft_dprintf(fd_write, "%%%d", ft_swap_int16((int16_t)value));
					else
						ft_dprintf(fd_write, "%%%d", ft_swap_int32((int32_t)value));
					if (index + 1 != g_op_tab[op_code - 1].number_registries)
						ft_dprintf(fd_write, ", ");
				}
				else if (args[index] & IND_CODE)
				{
					if (read(fd_read, &value, 2) < 0)
						return (0);
					ft_dprintf(fd_write, "%d",value);
					if (index + 1 != g_op_tab[op_code - 1].number_registries)
						ft_dprintf(fd_write, ", ");
				}
			}
		}
		else
		{
			index = -1;
			while (++index < g_op_tab[op_code - 1].number_registries)
			{
				value = 0;
				if (g_op_tab[op_code - 1].type_argument[0] & REG_CODE)
				{
					if (read(fd_read, &value, 1) < 0)
						return (0);
					ft_dprintf(fd_write, "r%d", value);
					if (index + 1 != g_op_tab[op_code - 1].number_registries)
						ft_dprintf(fd_write, ", ");
				}
				else if (g_op_tab[op_code - 1].type_argument[0] & DIR_CODE)
				{
					int byte = (g_op_tab[op_code - 1].changes_carry ? 2 : 4);
					if (read(fd_read, &value, byte) < 0)
						return (0);
					if (byte == 2)
						ft_dprintf(fd_write, "%%%d", ft_swap_int16((int16_t)value));
					else
						ft_dprintf(fd_write, "%%%d",ft_swap_int32((int32_t)value));
					if (index + 1 != g_op_tab[op_code - 1].number_registries)
						ft_dprintf(fd_write, ", ");
				}
				else if (g_op_tab[op_code - 1].type_argument[0] & IND_CODE)
				{
					if (read(fd_read, &value, 2) < 0)
						return (0);
					ft_dprintf(fd_write, "%d",value);
					if (index + 1 != g_op_tab[op_code - 1].number_registries)
						ft_dprintf(fd_write, ", ");
				}
			}
			
		}
		ft_dprintf(fd_write, "\n");
	}
	return (1);
}