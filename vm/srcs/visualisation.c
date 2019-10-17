/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:58:09 by cmarouan          #+#    #+#             */
/*   Updated: 2019/10/15 11:33:54 by cmarouan         ###   ########.fr       */
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
}

void put_players(t_player *players, int nb_p, WINDOW *info)
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
		sprintf(res, "Players %d : %s", i + 1, players[i].prog_name);
		wattron(info, COLOR_PAIR(3));
		mvwaddstr(info, x, y, res);
		sprintf(res, "Last live %d",  players[i].last_live);
		wattron(info, COLOR_PAIR(2));
		mvwaddstr(info, x + 1, y + 5, res);
		x = x + 2;
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
	mvwaddstr(w_info, 1, 5, "Running");
	wattron(w_info, COLOR_PAIR(2));
	sprintf(res, "Cycle : %d", vm->cycle_from_start);
	mvwaddstr(w_info, 5, 5, res);
	sprintf(res, "Process : %d", vm->pc_count);
	wattron(w_info, COLOR_PAIR(2));
	mvwaddstr(w_info, 6, 5, res);
	put_players(vm->players, vm->player_c, w_info);
	wrefresh(w_info);
}

void left_window(WINDOW *w_memory)
{
	int i = 0;
	int x = 3;
	int y = 1;
	int j = 0;
	
	box(w_memory, A_UNDERLINE, A_UNDERLINE ); 
	wbkgd(w_memory, COLOR_PAIR(1));
	wmove(w_memory, 1, 3);
	wrefresh(w_memory);
	while (j <= 63)
	{
		i = 0;
		while (i <= 63)
		{
			if (i == 0 && j == 0)
				wattron(w_memory, COLOR_PAIR(6));
			else
				wattron(w_memory, COLOR_PAIR(5));
			if (i == 0 && j == 32)
				wattron(w_memory, COLOR_PAIR(6));
			mvwaddstr(w_memory, y, x, "00");
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

void change_memory(int index, t_memory *mem, WINDOW *windowA)
{
	int x;
	int y;
	char byte[3];

	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	sprintf(byte, "%.2X", mem->byte);
	wattron(windowA, COLOR_PAIR(mem->p_id));
	mvwaddstr(windowA, x, y, byte);
	mvwaddstr(windowA, x, y + 2, " ");
}

int ft_int_vis(WINDOW **w_memory, WINDOW **w_info)
{
	int maxx;
	int maxy;
	int halfx;
	int halfy;

	initscr();
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


int main(void)
{
	WINDOW *w_memory;
	WINDOW *w_info;
	int ch;
	t_vm vm;

	if (ft_int_vus(&w_memory, &w_info))
	{
		left_window(w_memory);
		window_right(w_info, &vm);
	}
	usleep(500000);
	delwin(w_memory);
	delwin(w_info);
	endwin();
	return 0;
}
