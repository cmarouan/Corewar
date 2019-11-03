/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 21:18:11 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/03 21:21:52 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_sub(t_vm *vm, t_process *p)
{
	int		valide;
	int		r[3];
	int		index;

	index = p->pc - vm->memory;
	p->cycle_to_wait = -1;
	if ((valide = ft_valide(p->opcode, vm->memory, index)) > 0)
	{
		PC_INCR(vm, p, valide);
		return ;
	}
	index += 2;
	r[0] = vm->memory[MOD(index++)].byte - 1;
	r[1] = vm->memory[MOD(index++)].byte - 1;
	r[2] = vm->memory[MOD(index++)].byte - 1;
	p->reg[r[2]] = p->reg[r[0]] - p->reg[r[1]];
	if (p->reg[r[2]] == 0)
		p->carry = 1;
	else
		p->carry = 0;
	if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
		ft_printf("p %4d | sub r%d r%d r%d\n", p->pc_id, r[0], r[1], r[2]);
	index = index - (p->pc - vm->memory);
	PC_INCR(vm, p, index);
}
