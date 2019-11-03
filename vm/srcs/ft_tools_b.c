/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 23:21:09 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/03 23:21:52 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_check_magic(int fd, t_vm *vm)
{
	uint8_t	data[4];

	read(fd, data, 4);
	if (big_endian_to_int(data, 4) != COREWAR_EXEC_MAGIC)
	{
		ft_outerr(INVALID_MAGIC_CODE, vm);
	}
}

void		ft_read_null(int fd, t_vm *vm)
{
	int		i;
	uint8_t	data[4];

	read(fd, &data, 4);
	i = 0;
	while (i < 4)
		if (data[i++] != 0x00)
			ft_outerr(INVALID_NULL_BYTE, vm);
}

void	ft_change_pc(t_vm *vm, t_process *p, int value)
{
	int diff;

	p->oldindex = p->pc - vm->memory;
	diff = (p->pc - vm->memory) + value;
	if (diff >= 0 && diff < MEM_SIZE)
		p->pc += value;
	else if (diff >= MEM_SIZE)
		p->pc = vm->memory + diff - MEM_SIZE;
	else if (diff < 0)
		p->pc = vm->memory + MEM_SIZE + diff;
	if (vm->f_vus)
		ft_move_pc(p, vm);
}
