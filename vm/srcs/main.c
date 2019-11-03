/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:37:45 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/03 15:38:56 by kmoussai         ###   ########.fr       */
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
	ft_printf("%-13s : Run visualizer\n", "-v");
	exit(EXIT_SUCCESS);
}    


void	ft_outerr(int error, t_vm *vm)
{
	char	*terror[] =
	{
		"Invalid code size",
		"Invalid magic header",
		"Invalid norm file Null byte are not null"
	};
	if (errno != 0)
		perror("ERROR ");
	else
		ft_printf("ERROR : %s\n", terror[error]);
	ft_free_vm(vm);
	exit(EXIT_FAILURE);
}



int main(int argc, char **argv)
{
	t_vm *vm;

	if (argc <= 1)
        ft_usage();
	
	int i = 1;
	vm = ft_init_vm();
	ft_parse_args(argc, argv, vm);
	ft_parse_player_files(vm);
	ft_init_memory(vm);
	vm->instruction[0] = &ft_live;
	vm->instruction[1] = &ft_ld;
	vm->instruction[2] = &ft_st;
	vm->instruction[3] = &ft_add;
	vm->instruction[4] = &ft_sub;
	vm->instruction[5] = &ft_and;
	vm->instruction[6] = &ft_or;
	vm->instruction[7] = &ft_xor;
	vm->instruction[8] = &ft_zjmp;
	vm->instruction[9] = &ft_ldi;
	vm->instruction[10] = &ft_sti;
	vm->instruction[11] = &ft_fork;
	vm->instruction[12] = &ft_lld;
	vm->instruction[13] = &ft_lldi;
	vm->instruction[14] = &ft_lfork;
	vm->instruction[15] = &ft_aff;
	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < vm->player_c)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
						vm->players[i].id,vm->players[i].prog_size, vm->players[i].prog_name,vm->players[i].comment);
		vm->winner = (vm->players[vm->winner].id > vm->players[i].id ? vm->winner : i);
		i++;
	}
	if (vm->f_vus)
		vs_main(vm);
	if (ft_start(vm) == -1)
		return (0);
	vm->win = 1;
	if (vm->f_vus)
	{
		window_right(vm->w_info, vm);
		wgetch(vm->w_memory);
		delwin(vm->w_memory);
		delwin(vm->w_info);
		endwin();
	}
	//lunch winner;
	ft_printf("Contestant %d, \"%s\", has won !\n",
					vm->players[vm->winner].id, vm->players[vm->winner].prog_name);
	ft_free_vm(vm);
	return (0);
}

