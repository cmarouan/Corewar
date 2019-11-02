/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visualisation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:58:09 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/02 17:22:04 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h> 
#include "corewar.h"


void allocation_error(void)
{
	addstr("Unable to allocate memory for new window.\n");
	refresh();
	endwin();
	exit(1);
}

void initialize_colors()
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

void ft_put_players(int start, t_player *players, int nb_p, WINDOW *info)
{
	int i;
	char res[100];
	int x;
	int y;
	int id;

	i = 0;
	x = start + 2;
	y = 8;
	wattron(info, A_BOLD);
	sprintf(res, "Players : %d", nb_p);
	wattron(info, COLOR_PAIR(6));
	mvwaddstr(info, start + 2, 5, res);
	x++;
	while (i < nb_p)
	{
		id = players[i].id;
		sprintf(res, "Player -%d : %s", players[i].id, players[i].prog_name);
		wattron(info, COLOR_PAIR(id));
		mvwaddstr(info, x + 1, y, res);
		sprintf(res, "Last live %-8d",  players[i].last_live);
		wattron(info, COLOR_PAIR(5));
		mvwaddstr(info, x + 2, y + 5, res);
		x = x + 2;
		sprintf(res, "lives in current period %-8d",  players[i].live_in_current_period);
		wattron(info, COLOR_PAIR(5));
		mvwaddstr(info, x + 1, y + 5, res);
		x = x + 2;
		i++;
	}
	wmove(info, 0, 0);
	wrefresh(info);
}

void window_right(WINDOW *w_info, t_vm *vm)
{
	char res[50];
	int start = 0;

	wbkgd(w_info, COLOR_PAIR(2));
	wattron(w_info, COLOR_PAIR(6));
	wattron(w_info, A_BOLD);
	mvwprintw(w_info, ++start + 1, 5, vm->pause ? "Paused " : "Running");
	mvwprintw(w_info, ++start + 2, 5, "Speed : %.4d cycle/second", vm->speed);
	mvwprintw(w_info, ++start + 3, 5, "Cycle to die %-10d", vm->cycle_to_die);
	wattron(w_info, COLOR_PAIR(6));
	start += 2;
	mvwprintw(w_info, ++start + 2, 5, "Nbr of check : %.4d/%-20d", vm->nbr_of_check, MAX_CHECKS);
	start++;
	mvwprintw(w_info, ++start + 2, 5, "Cycle to check : %-7d", vm->current_cycle - 1);
	sprintf(res, "Cycle : %-8d", vm->cycle_from_start);
	start++;
	mvwaddstr(w_info, ++start + 2, 5, res);
	sprintf(res, "Process : %-20d", vm->pc_count);
	start++;
	mvwaddstr(w_info, ++start + 2, 5, res);
	start++;
	mvwprintw(w_info, ++start + 2, 5, "Nbr of lives : %.10d/%-20d", vm->nbr_live, NBR_LIVE);
	ft_put_players(++start + 2, vm->players, vm->player_c, w_info);
	if (vm->aff)
		mvwprintw(w_info, 32, 5, "AFF : %.10d", vm->aff_value);
	wattron(w_info, COLOR_PAIR(vm->players[vm->winner].id));
	if (vm->win)
	 	mvwprintw(w_info, 34, 5, "The winner is : %s", vm->players[vm->winner].prog_name);

	wrefresh(w_info);
}

void left_window(WINDOW *w_memory, t_memory *mem)
{
	int i = 0;
	int x = 3;
	int y = 1;
	int j = 0;
	uint8_t  data[3];
	
	wattron(w_memory, COLOR_PAIR(4));
	box(w_memory, 0, 0); 
	wbkgd(w_memory, COLOR_PAIR(1));
	wmove(w_memory, 1, 3);
	wrefresh(w_memory);
	while (j < 64)
	{
		i = 0;
		while (i < 64)
		{
			wattron(w_memory, COLOR_PAIR((mem[j*64 + i].p_id == 0 ? 5 : mem[j*64 + i].p_id)));
			sprintf((char *)data, "%.2x", mem[j*64 + i].byte);
			mvwaddstr(w_memory, y, x, (char *)data);
			wattron(w_memory, COLOR_PAIR(5));
			mvwaddstr(w_memory, y, x + 2, " ");
			x = x + 3;
			i++;
		}
		x = 3;
		y++;
		j++;
	}
	wrefresh(w_memory);
}

void ft_change_memory(int index, t_memory *mem, WINDOW *window)
{
	int x;
	int y;
	char byte[3];

	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	sprintf(byte, "%.2x", mem->byte);
	wattron(window, COLOR_PAIR(mem->p_id));
	mvwaddstr(window, x, y, byte);
	wrefresh(window);
}

int ft_int_vis(WINDOW **w_memory, WINDOW **w_info)
{
	int maxx;
	int maxy;
	int halfx;

	initscr();
	cbreak();
	noecho();
	nodelay(*w_info, true);
	keypad(stdscr, TRUE);
	start_color();
	initialize_colors();
	getmaxyx(stdscr, maxy, maxx);
	halfx = maxx >> 1;
	if ((*w_memory = newwin(66 , 197 , 0, 0)) == NULL)
		allocation_error();
	if ((*w_info = newwin(maxy - 5, halfx, 0, 202)) == NULL)
		allocation_error();
	return (1);
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
		}else if (cmd == 'a')
			return (0);
		else if (cmd == 's' || cmd == 'S')
			vm->speed = (vm->speed >= 1000 ? vm->speed : vm->speed + 10);
		else if (cmd == 'd' || cmd == 'D')
			vm->speed = (vm->speed >= 1000 ? vm->speed : vm->speed + 50);
		else if (cmd == 'f' || cmd == 'F')
			vm->speed = (vm->speed >= 1000 ? vm->speed : vm->speed + 100);
		else if (cmd == 'g' || cmd == 'g')
			vm->speed = 1;
		if (vm->pause)
		{
			window_right(vm->w_info, vm);
			cmd = wgetch(vm->w_info);
			continue;
		}
		return (0);
	}
}

void ft_move_pc(t_process *p, t_vm *vm)
{
	int x;
	int y;
	int index = p->pc - vm->memory;
	char byte[3];

	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	sprintf(byte, "%.2x", p->pc->byte);
	wattron(vm->w_memory, COLOR_PAIR(7));
	mvwaddstr(vm->w_memory, x, y, byte);
	wrefresh(vm->w_memory);
	wrefresh(vm->w_info);
	index = p->oldindex;
	if (index == -1)
		return;
	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	sprintf(byte, "%.2x", vm->memory[index].byte);
	wattron(vm->w_memory, COLOR_PAIR(vm->memory[index].p_id == 0 ? 5 : vm->memory[index].p_id));
	mvwaddstr(vm->w_memory, x, y, byte);
	wrefresh(vm->w_memory);
	wrefresh(vm->w_info);
}

void vs_main(t_vm *vm)
{
	if (ft_int_vis(&vm->w_memory, &vm->w_info))
	{
		curs_set(0);
		wrefresh(vm->w_memory);
		nodelay(vm->w_info, false);
		left_window(vm->w_memory, vm->memory);
		window_right(vm->w_info, vm);
	}

}
