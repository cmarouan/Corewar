/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:16:42 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/04 15:00:57 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		ft_args_value(t_vm *vm, int *ind, t_uint8 argtype)
{
	int		index;
	int		jump_val;
	t_uint8	data[4];

	index = *ind;
	argtype = vm->memory[MOD(index++)].byte >> SHIFT_ARG1;
	if (argtype == DIR_CODE)
	{
		ft_getbytes(vm->memory, vm->memory + (MOD(index)), 4, data);
		index += 4;
	}
	else
	{
		ft_getbytes(vm->memory, vm->memory + (MOD(index)), 2, data);
		jump_val = index - 2 + big_endian_to_int(data, 2);
		if (jump_val < 0)
			jump_val = MEM_SIZE + jump_val;
		ft_getbytes(vm->memory, vm->memory + MOD(jump_val), 4, data);
		index += 2;
	}
	*ind = index;
	return (big_endian_to_int(data, 4));
}

void			ft_lld(t_vm *vm, t_process *p)
{
	int jump_val;
	int argval;
	int index;

	index = p->pc - vm->memory;
	p->cycle_to_wait = -1;
	if ((jump_val = ft_valide(p->opcode, vm->memory, index++)) > 0)
	{
		PC_INCR(vm, p, jump_val);
		return ;
	}
	argval = ft_args_value(vm, &index, 0);
	if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
		ft_printf("p %4d | lld %d r%d\n", p->pc_id,
				argval, vm->memory[MOD(index)].byte);
	p->reg[vm->memory[MOD(index)].byte - 1] = argval;
	if (p->reg[vm->memory[MOD(index++)].byte - 1] == 0)
		p->carry = 1;
	else
		p->carry = 0;
	index = index - (p->pc - vm->memory);
	PC_INCR(vm, p, index);
}
