/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visualisation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:58:09 by cmarouan          #+#    #+#             */
/*   Updated: 2019/10/18 14:16:35 by kmoussai         ###   ########.fr       */
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
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_CYAN);
	init_pair(7, COLOR_BLACK, COLOR_WHITE);
	//init_pair(8, COLOR_BLACK, -1);
}

void ft_put_players(t_player *players, int nb_p, WINDOW *info)
{
	int i;
	char res[100];
	int x;
	int y;

	i = 0;
	x = 12;
	y = 8;
	sprintf(res, "Players : %d", nb_p);
	wattron(info, COLOR_PAIR(3));
	mvwaddstr(info, 10, 5, res);
	while (i < nb_p)
	{
		sprintf(res, "Player -%d : %s", players[i].id, players[i].prog_name);
		wattron(info, COLOR_PAIR(5));
		mvwaddstr(info, x, y, res);
		sprintf(res, "Last live %d",  players[i].last_live);
		wattron(info, COLOR_PAIR(2));
		mvwaddstr(info, x + 2, y + 5, res);
		x = x + 2;
		sprintf(res, "lives in current period %d",  players[i].live_in_current_period);
		wattron(info, COLOR_PAIR(2));
		mvwaddstr(info, x + 2, y + 5, res);
		x = x + 4;
		i++;
	}
	wrefresh(info);
}

void window_right(WINDOW *w_info, t_vm *vm)
{
	char res[50];

	wattron(w_info, A_BOLD);
	wbkgd(w_info, COLOR_PAIR(2));
	wattron(w_info, COLOR_PAIR(4));
	mvwprintw(w_info, 1, 5, !vm->pause ? "Running" : "Paused ");
	mvwprintw(w_info, 2, 5, "Speed : %.4d cycle/second", vm->speed);
	wattron(w_info, COLOR_PAIR(2));
	sprintf(res, "Cycle : %d", vm->cycle_from_start);
	mvwaddstr(w_info, 5, 5, res);
	sprintf(res, "Process : %d", vm->pc_count);
	mvwaddstr(w_info, 7, 5, res);
	ft_put_players(vm->players, vm->player_c, w_info);
	
	wrefresh(w_info);
}

void left_window(WINDOW *w_memory, t_memory *mem)
{
	int i = 0;
	int x = 3;
	int y = 1;
	int j = 0;
	uint8_t  data[3];
	
	box(w_memory, A_UNDERLINE, A_UNDERLINE ); 
	wbkgd(w_memory, COLOR_PAIR(1));
	wmove(w_memory, 1, 3);
	wrefresh(w_memory);
	while (j < 64)
	{
		i = 0;
		while (i < 64)
		{
			wattron(w_memory, COLOR_PAIR((mem[j*64 + i].p_id == -1 ? 5 : mem[j*64 + i].p_id)));
			sprintf((char *)data, "%.2X", mem[j*64 + i].byte);
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

void ft_change_memory(int index, t_memory *mem, WINDOW *windowA)
{
	int x;
	int y;
	char byte[3];

	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	sprintf(byte, "%.2X", mem->byte);
	wattron(windowA, COLOR_PAIR(mem->p_id));
	mvwaddstr(windowA, x, y, byte);
}

int ft_int_vis(WINDOW **w_memory, WINDOW **w_info)
{
	int maxx;
	int maxy;
	int halfx;

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	//delay(stdscr, true);
	//timeout();
	start_color();
	initialize_colors();
	getmaxyx(stdscr, maxy, maxx);
	halfx = maxx >> 1;
	if ((*w_memory = newwin(maxy - 5 , halfx + (halfx >> 1), 0, 0)) == NULL)
		allocation_error();
	if ((*w_info = newwin(maxy - 5, (halfx >> 1), 0, halfx + (halfx >> 1))) == NULL)
		allocation_error();
	if ( maxy < 72 || maxx <  264)
	{
		wattron(*w_memory, COLOR_PAIR(1));
		wprintw(*w_memory, "Small window");
		exit(0);
	}
	return (1);
}


int		ft_event_handler(t_vm *vm, int cmd)
{
	if (cmd == 27)
		return (1);
	if (cmd == 's' || cmd == 'S')
		vm->speed = (vm->speed >= 1000 ? vm->speed : vm->speed + 10);
	else if (cmd == 'd' || cmd == 'D')
		vm->speed = (vm->speed >= 1000 ? vm->speed : vm->speed + 50);
	else if (cmd == 'f' || cmd == 'F')
		vm->speed = (vm->speed >= 1000 ? vm->speed : vm->speed + 100);
	else if (cmd == 'g' || cmd == 'g')
		vm->speed = 1;
	else if (cmd == 'p' || cmd == 'P')
	{
		nodelay(vm->w_info, !vm->pause);
		vm->pause = !vm->pause;	
	}
		//vm->speed -= 100000;
	return (0);
}


void ft_move_pc(t_process *p, t_vm *vm)
{
	int x;
	int y;
	int index = p->pc - vm->memory;
	char byte[3];

	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	sprintf(byte, "%.2X", p->pc->byte);
	wattron(vm->w_memory, COLOR_PAIR(7));
	mvwaddstr(vm->w_memory, x, y, byte);
	wrefresh(vm->w_memory);

	index = p->oldindex;
	if (index == -1)
		return;
	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	sprintf(byte, "%.2X", vm->memory[index].byte);
	wattron(vm->w_memory, COLOR_PAIR(vm->memory[index].p_id == -1 ? 5 : vm->memory[index].p_id ));
	mvwaddstr(vm->w_memory, x, y, byte);
	wrefresh(vm->w_memory);
}


void vs_main(t_vm *vm)
{

	if (ft_int_vis(&vm->w_memory, &vm->w_info))
	{
		curs_set(0);
		wrefresh(vm->w_memory);
		left_window(vm->w_memory, vm->memory);
		window_right(vm->w_info, vm);
	}

}