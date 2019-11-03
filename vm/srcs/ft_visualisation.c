/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visualisation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:58:09 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/02 22:55:44 by cmarouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "corewar.h"

void	allocation_error(void)
{
	addstr("Unable to allocate memory for new window.\n");
	refresh();
	endwin();
	exit(1);
}

void	initialize_colors(void)
{
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_WHITE);
	init_pair(8, COLOR_BLACK, COLOR_BLACK);
}

void	ft_put_players(int start, t_player *players, int nb_p, WINDOW *info)
{
	int	i;
	int	x;
	int	y;
	int	id;

	i = 0;
	x = start + 3;
	y = 8;
	wattron(info, COLOR_PAIR(6));
	mvwprintw(info, start + 2, 5, "Players : %d", nb_p);
	while (i < nb_p)
	{
		id = players[i].id;
		wattron(info, COLOR_PAIR(id));
		mvwprintw(info, x + 1, y, "Player -%d : %s", players[i].id,
		players[i].prog_name);
		wattron(info, COLOR_PAIR(5));
		mvwprintw(info, x + 2, y + 5, "Last live %-8d", players[i].last_live);
		x = x + 2;
		wattron(info, COLOR_PAIR(5));
		mvwprintw(info, x + 1, y + 5, "lives in current period %-8d",
		players[i].live_in_current_period);
		x = x + 2;
		i++;
	}
}

void	write_help(WINDOW *w_info)
{
	wattron(w_info, COLOR_PAIR(6));
	mvwprintw(w_info, 48, 5, "Help");
	mvwprintw(w_info, 50, 7, "Start/Pause: Space");
	mvwprintw(w_info, 52, 7, "Step by step: A");
	mvwprintw(w_info, 54, 7, "Speed by:");
	mvwprintw(w_info, 56, 9, "G 1 cycle");
	mvwprintw(w_info, 58, 9, "S 10 cylcles");
	mvwprintw(w_info, 60, 9, "D 50 cylcles");
	mvwprintw(w_info, 62, 9, "F 100 cylcles");
}

int		infos(WINDOW *w_info, t_vm *vm)
{
	int	start;

	start = 0;
	wbkgd(w_info, COLOR_PAIR(2));
	wattron(w_info, COLOR_PAIR(6));
	wattron(w_info, A_BOLD);
	mvwprintw(w_info, ++start + 1, 5, vm->pause ? "Paused " : "Running");
	mvwprintw(w_info, ++start + 2, 5, "Speed : %.4d cycle/second", vm->speed);
	mvwprintw(w_info, ++start + 3, 5, "Cycle to die %-10d", vm->cycle_to_die);
	wattron(w_info, COLOR_PAIR(6));
	start += 2;
	mvwprintw(w_info, ++start + 2, 5, "Nbr of check : %.4d/%-20d",
	vm->nbr_of_check, MAX_CHECKS);
	start++;
	mvwprintw(w_info, ++start + 2, 5, "Cycle to check : %-7d",
	vm->current_cycle - 1);
	start++;
	mvwprintw(w_info, ++start + 2, 5, "Cycle : %-8d",
	vm->cycle_from_start);
	start++;
	mvwprintw(w_info, ++start + 2, 5, "Process : %-20d", vm->pc_count);
	start++;
	mvwprintw(w_info, ++start + 2, 5, "Nbr of lives : %.10d/%-20d",
	vm->nbr_live, NBR_LIVE);
	return (start);
}

void	window_right(WINDOW *w_info, t_vm *vm)
{
	int start;

	start = infos(w_info, vm);
	wattron(w_info, A_BOLD);
	ft_put_players(++start + 2, vm->players, vm->player_c, w_info);
	wmove(w_info, 0, 0);
	wrefresh(w_info);
	if (vm->aff)
		mvwprintw(w_info, 44, 5, "AFF : %-10d", vm->aff_value);
	wattron(w_info, COLOR_PAIR(vm->players[vm->winner].id));
	if (vm->win)
		mvwprintw(w_info, 46, 5, "The winner is : %s",
		vm->players[vm->winner].prog_name);
	wrefresh(w_info);
}

void	initial_left_window(WINDOW *w_memory)
{
	wattron(w_memory, COLOR_PAIR(4));
	box(w_memory, 0, 0);
	wbkgd(w_memory, COLOR_PAIR(1));
	wmove(w_memory, 1, 3);
	wrefresh(w_memory);
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
	wrefresh(w_memory);
}

void	ft_change_memory(int index, t_memory *mem, WINDOW *window)
{
	int	x;
	int	y;

	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	wattron(window, COLOR_PAIR(mem->p_id));
	mvwprintw(window, x, y, "%.2x", mem->byte);
	wrefresh(window);
}

int		ft_int_vis(WINDOW **w_memory, WINDOW **w_info)
{
	int	maxx;
	int	maxy;
	int	halfx;

	initscr();
	cbreak();
	noecho();
	nodelay(*w_info, true);
	keypad(stdscr, TRUE);
	start_color();
	initialize_colors();
	getmaxyx(stdscr, maxy, maxx);
	halfx = maxx >> 1;
	if ((*w_memory = newwin(66, 197, 0, 0)) == NULL)
		allocation_error();
	if ((*w_info = newwin(maxy - 5, halfx, 0, 202)) == NULL)
		allocation_error();
	return (1);
}

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
	wrefresh(vm->w_info);
	index = p->oldindex;
	if (index == -1)
		return ;
	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	wattron(vm->w_memory, COLOR_PAIR(vm->memory[index].p_id == 0 ? 5 :
	vm->memory[index].p_id));
	mvwprintw(vm->w_memory, x, y, "%.2x", vm->memory[index].byte);
	wrefresh(vm->w_memory);
	wrefresh(vm->w_info);
}

void	vs_main(t_vm *vm)
{
	if (ft_int_vis(&vm->w_memory, &vm->w_info))
	{
		curs_set(0);
		wrefresh(vm->w_memory);
		nodelay(vm->w_info, false);
		left_window(vm->w_memory, vm->memory);
		window_right(vm->w_info, vm);
		write_help(vm->w_info);
	}
}
