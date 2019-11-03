/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:16:42 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/03 17:24:43 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_lld(t_vm *vm, t_process *p)
{
	int			jump_val;
	uint8_t		argtype;
	t_memory	*tmp;
	uint8_t		data[4];
	int			index;

	index = p->pc - vm->memory;
	if ((jump_val = ft_valide(p->opcode, vm->memory, index)) > 0)
	{
		p->cycle_to_wait = -1;
		PC_INCR(vm, p, jump_val);
		return ;
	}
	tmp = p->pc;
	index++;
	argtype = vm->memory[MOD(index)].byte >> SHIFT_ARG1;
	index++;
	if (argtype == DIR_CODE)
	{
		ft_getbytes(vm->memory, vm->memory + (MOD(index)), 4, data);
		index += 4;
	}
	else
	{
		ft_getbytes(vm->memory, vm->memory + (MOD(index)), 2, data);
		jump_val = p->pc - vm->memory + big_endian_to_int(data, 2);
		if (jump_val < 0)
			jump_val = MEM_SIZE + jump_val;
		ft_getbytes(vm->memory, vm->memory + MOD(jump_val), 4, data);
		index += 2;
	}
	if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
		ft_printf("p %4d | lld %d r%d\n", p->pc_id,
				big_endian_to_int(data, 4), vm->memory[MOD(index)].byte);
	p->reg[vm->memory[MOD(index)].byte - 1] = big_endian_to_int(data, 4);
	if (p->reg[vm->memory[MOD(index)].byte - 1] == 0)
		p->carry = 1;
	else
		p->carry = 0;
	index++;
	p->cycle_to_wait = -1;
	index = index - (p->pc - vm->memory);
	PC_INCR(vm, p, index);
}
