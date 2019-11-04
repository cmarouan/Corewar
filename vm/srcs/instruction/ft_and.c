/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:31:39 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/04 15:00:57 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		ft_arg_one(t_vm *vm, t_uint8 *argtype, t_process *p, int *index)
{
	t_uint8 data[4];
	int		jump_val;

	if (*argtype >> SHIFT_ARG1 == DIR_CODE)
		ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 4, data);
	else if (*argtype >> SHIFT_ARG1 == IND_CODE)
	{
		ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
		jump_val = p->pc - vm->memory + big_endian_to_int(data, 2) % IDX_MOD;
		jump_val = jump_val < 0 ? MEM_SIZE + jump_val : jump_val;
		ft_getbytes(vm->memory, vm->memory + MOD(jump_val), 4, data);
		*index = *index + 2;
		*argtype ^= (IND_CODE << SHIFT_ARG1);
		return (big_endian_to_int(data, 4));
	}
	else
	{
		jump_val = vm->memory[*MOD(index)].byte - 1;
		*index = *index + 1;
		*argtype ^= (REG_CODE << SHIFT_ARG1);
		return (p->reg[jump_val]);
	}
	*argtype ^= (DIR_CODE << SHIFT_ARG1);
	*index = *index + 4;
	return (big_endian_to_int(data, 4));
}

static int		ft_arg_two(t_vm *vm, t_uint8 *argtype, t_process *p, int *index)
{
	t_uint8 data[4];
	int		jump_val;

	if (*argtype >> SHIFT_ARG2 == DIR_CODE)
		ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 4, data);
	else if (*argtype >> SHIFT_ARG2 == IND_CODE)
	{
		ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
		jump_val = p->pc - vm->memory + big_endian_to_int(data, 2) % IDX_MOD;
		jump_val = jump_val < 0 ? MEM_SIZE + jump_val : jump_val;
		ft_getbytes(vm->memory, vm->memory + MOD(jump_val), 4, data);
		*index = *index + 2;
		*argtype ^= (IND_CODE << SHIFT_ARG2);
		return (big_endian_to_int(data, 4));
	}
	else
	{
		jump_val = vm->memory[*MOD(index)].byte - 1;
		*index = *index + 1;
		*argtype ^= (REG_CODE << SHIFT_ARG2);
		return (p->reg[jump_val]);
	}
	*argtype ^= (DIR_CODE << SHIFT_ARG2);
	*index = *index + 4;
	return (big_endian_to_int(data, 4));
}

void			ft_and(t_vm *vm, t_process *p)
{
	t_uint8	argtype;
	int		val[3];
	int		index;

	index = p->pc - vm->memory;
	p->cycle_to_wait = -1;
	if ((val[2] = ft_valide(p->opcode, vm->memory, index++)) > 0)
	{
		PC_INCR(vm, p, val[2]);
		return ;
	}
	argtype = vm->memory[MOD(index++)].byte;
	val[0] = ft_arg_one(vm, &argtype, p, &index);
	val[1] = ft_arg_two(vm, &argtype, p, &index);
	p->reg[vm->memory[MOD(index)].byte - 1] = val[0] & val[1];
	if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
		ft_printf("p %4d | And %d %d r%d\n", p->pc_id,
				val[0], val[1], vm->memory[MOD(index)].byte);
	if (p->reg[vm->memory[MOD(index++)].byte - 1] == 0)
		p->carry = 1;
	else
		p->carry = 0;
	index = index - (p->pc - vm->memory);
	PC_INCR(vm, p, index);
}
