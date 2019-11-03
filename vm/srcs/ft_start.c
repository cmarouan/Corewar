#include "corewar.h"


int ft_start(t_vm *vm)
{
	//int ret;
	
	vm->cycle_from_start = 0;
	vm->current_cycle = vm->cycle_to_die;
	while (vm->current_cycle > 0)
	{
		if (vm->f_vus)
		{
			//wgetch(vm->w_info);
			if (ft_event_handler(vm, wgetch(vm->w_info)) == -1)
			  	break;
			window_right(vm->w_info, vm);
			wrefresh(vm->w_memory);
			usleep(SECOND / vm->speed);
		}
		t_process *tmp = vm->process;
		vm->cycle_from_start++;
		while (tmp)
		{
				if (tmp->cycle_to_wait <= 0)
					ft_exec(tmp, vm);
				if (tmp->cycle_to_wait > -1)
					tmp->cycle_to_wait--;
				if (vm->f_vus)
					window_right(vm->w_info, vm);
			tmp = tmp->next;
		}
		if (vm->current_cycle == 1)
		{
			ft_check(vm);
			if (vm->f_vus)
				window_right(vm->w_info, vm);
			vm->current_cycle = vm->cycle_to_die;
		}else
			vm->current_cycle--;
		if (!vm->process)
			break;
		if (vm->f_dump > 0 && vm->f_dump == vm->cycle_from_start && !vm->f_vus)
		{
			print_mem(vm->memory);
			ft_free_vm(vm);
			return (-1);
		}
		if (vm->f_show > 0 && !(vm->cycle_from_start % vm->f_show) && !vm->f_vus)
		{
			print_mem(vm->memory);
			char c;
			read(0, &c, 1);
		}
	}
	return (1);
}