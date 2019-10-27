
#include "corewar.h"

t_vm	*ft_init_vm()
{
	t_vm *vm;
	
	
	vm = (t_vm *)malloc(sizeof(t_vm));
	vm->f_dump = -1;
	vm->f_show = -1;
	vm->f_vus = 0;
	vm->f_log = 0;
	vm->player_c = 0;
	vm->process = NULL;
	vm->pc_count = 0;
	vm->nbr_live = 0;
	vm->current_cycle = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_from_start = 0;
	vm->last_live_player = 0;
	vm->memory = NULL;
	vm->nbr_of_check = 0;
	vm->speed = 1;
	vm->pause = 1;
	vm->pc_count = 0;
	int i =0;
	vm->w_memory = NULL;
	vm->w_info = NULL;
	ft_bzero(vm->ids, sizeof(int) * (MAX_PLAYERS + 1));
	//vm->players = (t_player *)malloc(sizeof(t_player) * MAX_PLAYERS);
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
	return (vm);
}


void ft_init_memory(t_vm *vm)
{
	int i = -1;
	vm->memory = (t_memory *)malloc(sizeof(t_memory) * MEM_SIZE);
	while (++i < MEM_SIZE)
	{
		vm->memory[i].byte = 0;
		vm->memory[i].p_id = -1;
	}
	
	int j;
	i = 0;
	while (i < vm->player_c)
	{
		j = (MEM_SIZE/vm->player_c)*i;
		int h = 0;
		vm->process = ft_add_pc(vm, MOD(j), &vm->players[i]);
		//ft_printf("player code : %#p %d\n", &vm->players[i].code[h], h);
		//
		while (h < vm->players[i].prog_size)
		{
			
			vm->memory[j%MEM_SIZE].byte = vm->players[i].code[h];
			vm->memory[j%MEM_SIZE].p_id = vm->players[i].id;
			//exit(0);
			h++;
			j++;
		}
	//	free(vm->players[i].code);
		i++;
	}
	//ft_printf("%#p\n", &vm->players[i].code[0]);

}