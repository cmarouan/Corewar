/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:13:23 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/03 23:23:55 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_argsize(uint8_t opcode, uint8_t arg)
{
	if (arg == 0b01)
		return (1);
	else if (arg == 0b10)
		return (g_op_tab[opcode - 1].dir_size);
	else if (arg == 0b11)
		return (2);
	return (0);
}

int		ft_valide(uint8_t opcode, t_memory *mem, int index)
{
	int		size;
	int		i;
	int		wrong;
	int		arg;
	uint8_t	argtype;

	argtype = mem[(index + 1) % MEM_SIZE].byte;
	index += 2;
	i = 0;
	size = 0;
	wrong = 0;
	if (opcode < 1 || opcode > 16)
		return (2);
	while (i < g_op_tab[opcode - 1].argc)
	{
		arg = argtype >> (6 - i * 2);
		arg = (arg == 0b11 ? 4 : arg);
		if (arg == 0b01)
			if (mem[(index + size) % MEM_SIZE].byte <= 0 ||
					mem[(index + size) % MEM_SIZE].byte > 16)
				wrong++;
		size += ft_argsize(opcode, (arg == 4 ? 0b11 : arg));
		if ((arg & g_op_tab[opcode - 1].args[i]) == 0)
			wrong++;
		arg = (arg == 4 ? 0b11 : arg);
		argtype = argtype ^ (arg << (6 - i * 2));
		i++;
	}
	return (wrong ? size + 2 : -1);
}
