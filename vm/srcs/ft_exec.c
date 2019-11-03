/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:43:06 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/03 16:43:52 by cmarouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_exec(t_process *p, t_vm *vm)
{
	if (p->cycle_to_wait <= -1)
	{
		if (p->pc->byte > 0 && p->pc->byte <= 16)
		{
			p->opcode = p->pc->byte;
			p->cycle_to_wait = op_tab[p->opcode - 1].cycle - 1;
		}
		else
			PC_INCR(vm, p, 1);
		if (p->oldindex == -1)
			ft_move_pc(p, vm);
	}
	else if (p->cycle_to_wait == 0)
	{
		if (p->opcode >= 1 && p->opcode <= 16)
			vm->instruction[p->opcode - 1](vm, p);
		else
			PC_INCR(vm, p, 1);
	}
}
