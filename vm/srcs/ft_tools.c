/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:09:19 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/04 15:00:57 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_write_mem(t_vm *vm, const char *data,
		t_memory *mem, t_player *p)
{
	int i;

	i = 3;
	while (i >= 0)
	{
		if ((mem - vm->memory) >= MEM_SIZE)
			mem = mem - MEM_SIZE;
		mem->byte = data[i];
		mem->p_id = p->id;
		if (vm->f_vus)
			ft_change_memory(mem - vm->memory, mem, vm->w_memory);
		mem++;
		i--;
	}
}

void	ft_getbytes(t_memory *mem, t_memory *pc, int size, t_uint8 *data)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if ((pc - mem) >= MEM_SIZE)
			pc = pc - MEM_SIZE;
		data[i] = pc->byte;
		pc++;
		i++;
	}
}

int		big_endian_to_int(t_uint8 *data, int size)
{
	int neg;
	int result;
	int i;

	i = -1;
	result = 0;
	neg = *data & 0x80;
	while (++i < size)
		result |= ((0 + data[i]) << (size - 1 - i) * 8);
	if (neg && size == 2)
		return (result - 0xFFFF - 1);
	return (result);
}

void	print_mem(t_memory *memory)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 128)
	{
		j = 0;
		if (i == 0)
			ft_printf("0x0000 : ");
		else
			ft_printf("%#.4x : ", i * 32);
		while (j < 32)
		{
			ft_printf("%.2x ", memory[i * 32 + j].byte);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
