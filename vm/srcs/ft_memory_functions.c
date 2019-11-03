/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 15:05:34 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/03 23:16:50 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_event_case(t_vm *vm, int cmd)
{
	if (cmd == 's' || cmd == 'S')
		vm->speed = (vm->speed >= 1000 ? vm->speed : vm->speed + 10);
	else if (cmd == 'd' || cmd == 'D')
		vm->speed = (vm->speed >= 1000 ? vm->speed : vm->speed + 50);
	else if (cmd == 'f' || cmd == 'F')
		vm->speed = (vm->speed >= 1000 ? vm->speed : vm->speed + 100);
	else if (cmd == 'g' || cmd == 'g')
		vm->speed = 1;
}

int		ft_event_handler(t_vm *vm, int cmd)
{
	while (1)
	{
		if (cmd == 27)
			return (-1);
		else if (cmd == ' ')
		{
			nodelay(vm->w_info, vm->pause);
			vm->pause = !vm->pause;
			return (0);
		}
		if (cmd == 'a')
			return (0);
		else
			ft_event_case(vm, cmd);
		if (vm->pause)
		{
			window_right(vm->w_info, vm);
			cmd = wgetch(vm->w_info);
			continue;
		}
		return (0);
	}
}

void	initial_left_window(WINDOW *w_memory)
{
	wattron(w_memory, COLOR_PAIR(4));
	box(w_memory, 0, 0);
	wbkgd(w_memory, COLOR_PAIR(1));
	wmove(w_memory, 1, 3);
}

void	ft_move_pc(t_process *p, t_vm *vm)
{
	int	x;
	int	y;
	int	index;

	index = p->pc - vm->memory;
	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	wattron(vm->w_memory, COLOR_PAIR(7));
	mvwprintw(vm->w_memory, x, y, "%.2x", p->pc->byte);
	wrefresh(vm->w_memory);
	index = p->oldindex;
	if (index == -1)
		return ;
	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	wattron(vm->w_memory, COLOR_PAIR(vm->memory[index].p_id == 0 ? 5 :
				vm->memory[index].p_id));
	mvwprintw(vm->w_memory, x, y, "%.2x", vm->memory[index].byte);
	wrefresh(vm->w_memory);
}

void	left_window(WINDOW *w_memory, t_memory *mem)
{
	int	i;
	int	x;
	int	y;
	int	j;

	x = 3;
	y = 1;
	j = -1;
	initial_left_window(w_memory);
	while (++j < 64)
	{
		i = -1;
		while (++i < 64)
		{
			wattron(w_memory, COLOR_PAIR((mem[j * 64 + i].p_id == 0 ? 5 :
							mem[j * 64 + i].p_id)));
			mvwprintw(w_memory, y, x, "%.2x", mem[j * 64 + i].byte);
			wattron(w_memory, COLOR_PAIR(5));
			mvwprintw(w_memory, y, x + 2, " ");
			x = x + 3;
		}
		x = 3;
		y++;
	}
}
