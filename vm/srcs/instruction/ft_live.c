/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:09:25 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/04 15:00:57 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_live(t_vm *vm, t_process *p)
{
	t_uint8 data[4];
	int		ind;
	int		i;

	ind = p->pc - vm->memory + 1;
	vm->nbr_live++;
	p->live_declare++;
	p->cycle_to_wait = -1;
	ft_getbytes(vm->memory, vm->memory + MOD(ind), 4, data);
	PC_INCR(vm, p, 5);
	ind = -1 * big_endian_to_int(data, 4);
	i = 0;
	if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
		ft_printf("P %4d | live %d\n", p->pc_id, -1 * ind);
	while (i < vm->player_c && vm->players[i].id != ind)
		i++;
	if (i == vm->player_c)
		return ;
	if (vm->f_log == LIVES_LOG && !vm->f_vus)
		ft_printf("A process shows that player %d (%s) is alive at %d\n",
				vm->players[i].id, vm->players[i].prog_name,
				vm->cycle_from_start);
	vm->players[i].last_live = vm->cycle_from_start;
	vm->players[i].live_in_current_period++;
	vm->winner = i;
}
