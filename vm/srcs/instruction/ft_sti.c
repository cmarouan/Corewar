/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 21:46:49 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/03 21:53:20 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	ft_arg_two(t_vm *vm, uint8_t *argtype, t_process *p, int *index)
{
	uint8_t data[4];
	int		jump_val;

	if (*argtype >> SHIFT_ARG2 == DIR_CODE)
		ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
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
	*index = *index + 2;
	return (big_endian_to_int(data, 2));
}

static int	ft_arg_three(t_vm *vm, uint8_t *argtype, t_process *p, int *index)
{
	uint8_t	data[4];
	int		reg_index;

	if (*argtype >> SHIFT_ARG3 == DIR_CODE)
	{
		ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
		*index = *index + 2;
		return (big_endian_to_int(data, 2));
	}
	else
	{
		reg_index = vm->memory[*MOD(index)].byte - 1;
		*index = *index + 1;
		return (p->reg[reg_index]);
	}
}

void		ft_sti(t_vm *vm, t_process *p)
{
	uint8_t	argtype;
	int		val[3];
	int		index;

	index = p->pc - vm->memory;
	p->cycle_to_wait = -1;
	if ((val[2] = ft_valide(p->opcode, vm->memory, index++)) > 0)
	{
		PC_INCR(vm, p, val[2]);
		return ;
	}
	argtype = vm->memory[MOD(index++)].byte ^ (REG_CODE << SHIFT_ARG1);
	val[2] = vm->memory[MOD(index++)].byte;
	val[0] = ft_arg_two(vm, &argtype, p, &index);
	val[1] = ft_arg_three(vm, &argtype, p, &index);
	if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
		ft_printf("p %4d | sti r%d %d %d\n %7s -> store %.8X to %d (%d)\n",
				p->pc_id, val[2], val[0], val[1], "|", p->reg[val[2] - 1],
				(val[0] + val[1]) % IDX_MOD, vm->cycle_from_start);
	val[1] = (val[0] + val[1]) % IDX_MOD;
	val[1] = (p->pc - vm->memory) + val[1];
	val[1] = val[1] < 0 ? MEM_SIZE + val[1] : val[1];
	val[0] = p->reg[val[2] - 1];
	ft_write_mem(vm, (char *)&val[0], 4, vm->memory + MOD(val[1]), p->player);
	PC_INCR(vm, p, index - (p->pc - vm->memory));
}
