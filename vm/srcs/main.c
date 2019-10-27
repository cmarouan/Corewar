/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:37:45 by kmoussai          #+#    #+#             */
/*   Updated: 2019/10/26 20:25:39 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void ft_usage(void)
{
    ft_printf("usage : ./corewar [(-dump | -d) <N>] [-log] [-s <N>]");
	ft_printf(" [-v] [-n <N> <champion.cor>]");
	ft_printf(" [<champion.cor> <champion.cor> <...>]\n");
	ft_printf("-(d/dump) <N> : Dumps memory after N cycles then exits\n");
	ft_printf("%-9s <N> : Set <N> of the next player\n", "-n");
	ft_printf("%-9s <N> : Runs N cycles, dumps memory, pauses", "-s");
	ft_printf(",then repeats\n%-9s <N> : Logs levels\n", "-log");
	ft_printf("%20d : %s", 1, "Show Lives\n");
	ft_printf("%20d : %s", 2, "Show Cycles\n");
	ft_printf("%20d : %s", 4, "Show Operations\n");
	ft_printf("%20d : %s", 8, "Show Deaths\n");
	ft_printf("%20d : %s", 16, "Show PC movements\n");
	ft_printf("%-13s : Run visualizer\n", "-v");
	exit(0);
}    

void	ft_outerr(char *msg)
{
	
	ft_printf("ERROR : %s\n", msg);
	exit(0);
}



int main(int argc, char **argv)
{
	t_vm *vm;

	if (argc == 1 && argv[0])
        ft_usage();
	vm = ft_parse_args(argc - 1, argv);
	ft_parse_player_files(vm);
	vm->last_live_player = vm->player_c;
	ft_init_memory(vm);
	vm->instruction[0] = &ft_live;
	vm->instruction[1] = &ft_ld;
	vm->instruction[2] = &ft_st;
	vm->instruction[3] = &ft_add;
	vm->instruction[4] = &ft_sub;
		vm->instruction[5] = &ft_and;
		vm->instruction[6] = &ft_sti;
		vm->instruction[7] = &ft_sti;
	vm->instruction[8] = &ft_zjmp;
		vm->instruction[9] = &ft_sti;
		vm->instruction[10] = &ft_sti;
	vm->instruction[11] = &ft_sti;
		vm->instruction[12] = &ft_sti;
		vm->instruction[13] = &ft_sti;
		vm->instruction[14] = &ft_sti;
		vm->instruction[15] = &ft_sti;
	if (vm->f_vus)
	{
		vs_main(vm);
		while (wgetch(vm->w_info) != ' ');
		vm->pause = !vm->pause;
		nodelay(vm->w_info, true);	
	}
	ft_start(vm);

	if (vm->f_vus)
	{
		wgetch(vm->w_memory);
		delwin(vm->w_memory);
		delwin(vm->w_info);
		endwin();
	}
	//ft_free_vm(vm);
	return (0);
}

