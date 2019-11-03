/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 22:48:04 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/03 22:52:36 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_init_player(t_vm *vm)
{
	int i;

	i = 0;
	vm->player_c = 0;
	vm->winner = 0;
	vm->nbr_of_check = 0;
	vm->ids = (int *)malloc(sizeof(int) * (MAX_PLAYERS + 1));
	ft_bzero(vm->ids, sizeof(int) * (MAX_PLAYERS + 1));
	vm->players = (t_player *)malloc(sizeof(t_player) * MAX_PLAYERS);
	while (i < MAX_PLAYERS)
	{
		vm->players[i].id_set = 0;
		vm->players[i].id = -1;
		vm->players[i].file_name = NULL;
		vm->players[i].last_live = 0;
		ft_bzero(vm->players[i].prog_name, PROG_NAME_LENGTH + 1);
		vm->players[i].prog_size = 0;
		ft_bzero(vm->players[i].comment, COMMENT_LENGTH + 1);
		vm->players[i].code = NULL;
		i++;
	}
}

t_vm		*ft_init_vm(void)
{
	t_vm *vm;

	vm = (t_vm *)malloc(sizeof(t_vm));
	ft_memset(vm, 0, sizeof(vm));
	vm->win = 0;
	vm->aff = 0;
	vm->f_dump = -1;
	vm->f_show = -1;
	vm->f_vus = 0;
	vm->f_log = 0;
	vm->process = NULL;
	vm->pc_count = 0;
	vm->nbr_live = 0;
	vm->current_cycle = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_from_start = 0;
	vm->memory = NULL;
	vm->speed = 1;
	vm->pause = 1;
	vm->pc_ids = 0;
	vm->pc_count = 0;
	vm->w_memory = NULL;
	vm->w_info = NULL;
	ft_init_player(vm);
	return (vm);
}

void		ft_init_memory(t_vm *vm)
{
	int i;
	int j;
	int h;

	vm->memory = (t_memory *)malloc(sizeof(t_memory) * MEM_SIZE);
	ft_bzero(vm->memory, sizeof(t_memory) * MEM_SIZE);
	i = 0;
	while (i < vm->player_c)
	{
		j = (MEM_SIZE / vm->player_c) * i;
		h = 0;
		vm->process = ft_add_pc(vm, MOD(j), &vm->players[i]);
		while (h < vm->players[i].prog_size)
		{
			vm->memory[j % MEM_SIZE].byte = vm->players[i].code[h];
			vm->memory[j % MEM_SIZE].p_id = vm->players[i].id;
			h++;
			j++;
		}
		i++;
	}
}
