/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:29:36 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/03 16:31:13 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_aff(t_vm *vm, t_process *p)
{
	int		index;
	int		jump;

	index = p->pc - vm->memory;
	if ((jump = ft_valide(p->opcode, vm->memory, index)) > 0)
	{
		PC_INCR(vm, p, jump);
		p->cycle_to_wait = -1;
		return ;
	}
	index += 2;
	if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
		ft_printf("p %4d | aff r%d\n", p->pc_id, vm->memory[MOD(index)].byte);
	vm->aff_value = p->reg[vm->memory[MOD(index)].byte - 1];
	index++;
	vm->aff = 1;
	PC_INCR(vm, p, index - (p->pc - vm->memory));
}
