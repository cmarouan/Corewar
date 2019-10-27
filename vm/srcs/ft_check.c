
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
	int i = 0;
	while (i < vm->player_c)
	{
		vm->players[i].live_in_current_period = 0;
		i++;
	}



    
}