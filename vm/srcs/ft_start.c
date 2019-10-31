#include "corewar.h"


void ft_start(t_vm *vm)
{
	//int i = 0;
	vm->cycle_from_start = 1;
	vm->current_cycle = 1;
	while (vm->current_cycle <= vm->cycle_to_die)
	{
		
		t_process *tmp = vm->process;
		while (tmp)
		{
			if (tmp->kill)
			{
				if (tmp->cycle_to_wait <= 0)
				ft_exec(tmp, vm);
			if (tmp->cycle_to_wait > -1)
				tmp->cycle_to_wait--;
			if (vm->f_vus)
				window_right(vm->w_info, vm);
			}
			tmp = tmp->next;
		}
		if ( vm->current_cycle == vm->cycle_to_die)
		{
			ft_check(vm);
			vm->current_cycle = 0;
		}
		if (vm->f_dump > 0 && vm->f_dump == vm->cycle_from_start)
		{
			print_mem(vm->memory);
			break;
		}
		vm->cycle_from_start++;
		vm->current_cycle++;
		if (vm->f_vus)
		{
			if (ft_event_handler(vm, wgetch(vm->w_info)))
				break;
			window_right(vm->w_info, vm);
			wrefresh(vm->w_memory);
			usleep(SECOND / vm->speed);
		}
	}
}