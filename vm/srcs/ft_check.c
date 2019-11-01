
#include "corewar.h"

void ft_check(t_vm *vm)
{
	vm->nbr_of_check++;

	if (vm->nbr_live >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->nbr_of_check = 0;
	}
	else if (vm->nbr_of_check >= MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->nbr_of_check = 0;
	}
	vm->nbr_live = 0;
	//ft_printf("start %d\n",vm->cycle_from_start);
	int i = 0;
	while (i < vm->player_c)
	{
		vm->players[i].live_in_current_period = 0;
		i++;
	}
	
	vm->process = ft_kill_process(vm);
	
	if (vm->f_vus)
        wrefresh(vm->w_info);
}