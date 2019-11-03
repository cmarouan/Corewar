/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_exec_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 23:10:48 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 19:45:47 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		get_label_address(t_file *file, int src, int dst)
{
	int result;
	int sign;

	result = 0;
	sign = 1;
	if (src < dst)
	{
		while (src < dst)
		{
			result += file->code[src].number_byte;
			src++;
		}
	}
	else
	{
		sign = -1;
		while (src-- > dst)
			result += file->code[src].number_byte;
	}
	return (result * sign);
}

static int		get_argument_type(t_token *token)
{
	int number;
	int index;
	int shift;

	index = -1;
	shift = 6;
	number = 0;
	while (++index < token->nb_arg)
	{
		number |= token->args[index].code_arg << shift;
		shift -= 2;
	}
	return (number);
}

static t_byte	arg_dir_ind(t_file *file, int index, int index2, int index3)
{
	t_byte byte;

	byte.nb_byte = (g_op_tab[index2].changes_carry ||
			(file->code[index].args[index3].type_arg & T_IND)) ? 2 : 4;
	if (file->code[index].args[index3].label_index != -1)
		byte.number = get_label_address(file, index,
				file->code[index].args[index3].label_index);
	else
	{
		if (file->code[index].args[index3].type_arg & T_DIR)
			byte.number = ft_atoi(file->code[index].args[index3].arg + 1);
		else
			byte.number = ft_atoi(file->code[index].args[index3].arg);
	}
	return (byte);
}

static void		ft_print_args(t_file *file, int index, int index2, int fd)
{
	t_byte	byte_info;
	int		index3;

	index3 = -1;
	while (++index3 < file->code[index].nb_arg)
	{
		byte_info.nb_byte = 1;
		if (file->code[index].args[index3].type_arg & T_REG)
			byte_info.number = ft_atoi(file->code[index].args[index3].arg + 1);
		else
			byte_info = arg_dir_ind(file, index, index2, index3);
		ft_putbits_fd((char *)&byte_info.number, byte_info.nb_byte, fd);
	}
}

int				champion_exec_code(t_file *file, int fd)
{
	int index;
	int index2;
	int number;

	index = -1;
	while (file->code[++index].line)
	{
		if (file->code[index].number_byte)
		{
			index2 = check_instruction(file->code[index].instruction);
			ft_putbits_fd((char *)&g_op_tab[index2].opcode, 1, fd);
			if (g_op_tab[index2].argument_type_code)
			{
				number = get_argument_type(&file->code[index]);
				ft_putbits_fd((char *)&number, 1, fd);
			}
			ft_print_args(file, index, index2, fd);
		}
	}
	return (1);
}
