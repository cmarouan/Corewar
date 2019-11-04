/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:31:11 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/04 15:00:57 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_zjmp(t_vm *vm, t_process *p)
{
	int			dir;
	t_uint8		data[2];
	t_memory	*tmp;
	int			index;

	index = p->pc - vm->memory;
	tmp = p->pc;
	index++;
	ft_getbytes(vm->memory, vm->memory + MOD(index), 2, data);
	dir = big_endian_to_int(data, 2) % IDX_MOD;
	if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
		ft_printf("p %4d | zjmp %d %s\n",
				p->pc_id, dir, p->carry ? "OK" : "FAILED");
	p->cycle_to_wait = -1;
	if (p->carry == 0)
		PC_INCR(vm, p, 3);
	else
		PC_INCR(vm, p, dir);
}
