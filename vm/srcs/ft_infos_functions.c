/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infos_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 15:02:21 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/03 15:02:23 by cmarouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "corewar.h"

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
	if (vm->aff)
		mvwprintw(w_info, 44, 5, "AFF : %-10d", vm->aff_value);
	wattron(w_info, COLOR_PAIR(vm->players[vm->winner].id));
	if (vm->win)
		mvwprintw(w_info, 46, 5, "The winner is : %s",
		vm->players[vm->winner].prog_name);
	wrefresh(w_info);
}
