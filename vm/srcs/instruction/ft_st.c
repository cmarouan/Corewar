/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:56:12 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/04 15:00:57 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	ft_arg_two(t_vm *vm, t_process *p, int index, t_uint8 argtype)
{
	int		result;
	t_uint8	data[4];
	int		jump_val;

	result = vm->memory[MOD(index++)].byte - 1;
	if (argtype == REG_CODE)
		p->reg[vm->memory[MOD(index)].byte - 1] = p->reg[result];
	else
	{
		ft_getbytes(vm->memory, vm->memory + MOD(index), 2, data);
		jump_val = index - 3 + big_endian_to_int(data, 2) % IDX_MOD;
		if (jump_val < 0)
			jump_val = MEM_SIZE + jump_val;
		ft_write_mem(vm, (char *)&p->reg[result], vm->memory + MOD(jump_val),
				p->player);
		index++;
	}
	jump_val = big_endian_to_int(data, 2) % IDX_MOD;
	if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
		ft_printf("p %4d | st r%d %d\n", p->pc_id, result + 1,
			argtype == REG_CODE ? vm->memory[MOD((index - 1))].byte : jump_val);
	return (index + 1);
}

void		ft_st(t_vm *vm, t_process *p)
{
	int		jump_val;
	t_uint8 argtype;
	int		index;

	index = p->pc - vm->memory;
	p->cycle_to_wait = -1;
	if ((jump_val = ft_valide(p->opcode, vm->memory, index++)) > 0)
	{
		PC_INCR(vm, p, jump_val);
		return ;
	}
	argtype = vm->memory[MOD(index++)].byte ^ (REG_CODE << SHIFT_ARG1);
	argtype = argtype >> SHIFT_ARG2;
	index = ft_arg_two(vm, p, index, argtype);
	index = index - (p->pc - vm->memory);
	PC_INCR(vm, p, index);
}
