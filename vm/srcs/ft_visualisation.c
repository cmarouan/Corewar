/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visualisation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:58:09 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/03 15:38:25 by kmoussai         ###   ########.fr       */
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
	perror("ERROR ");
	exit(EXIT_FAILURE);
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

void	ft_change_memory(int index, t_memory *mem, WINDOW *window)
{
	int	x;
	int	y;

	x = (index / 64) + 1;
	y = ((index % 64) * 3) + 3;
	wattron(window, COLOR_PAIR(mem->p_id));
	mvwprintw(window, x, y, "%.2x", mem->byte);
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

void	vs_main(t_vm *vm)
{
	if (ft_int_vis(&vm->w_memory, &vm->w_info))
	{
		curs_set(0);
		nodelay(vm->w_info, false);
		left_window(vm->w_memory, vm->memory);
		wrefresh(vm->w_memory);
		window_right(vm->w_info, vm);
		write_help(vm->w_info);
	}
}
