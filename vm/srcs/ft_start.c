#include "corewar.h"


void ft_start(t_vm *vm)
{
    	
	//int i = 0;
	vm->cycle_from_start = 1;
	vm->current_cycle = 1;
	while (vm->current_cycle <= vm->cycle_to_die)
	{
		if ( vm->current_cycle == vm->cycle_to_die)
		{
			ft_check(vm);
			vm->current_cycle = 1;
		}

		t_process *tmp = vm->process;
		//ft_printf("Cycle  %d : pc at %d\n",vm->cycle_from_start, tmp->pc - vm->memory + 1);
		while (tmp)
		{
				
			//ft_printf("mem start from %X\n", vm->memory);
			if (tmp->cycle_to_wait <= 0)
				ft_exec(tmp, vm);
			tmp->cycle_to_wait--;
			
			//ft_change_memory(tmp->pc - vm->memory, tmp->pc, vm->w_memory);
			//if (vm->current_cycle >= vm->cycle_to_die)
			//	ft_check(vm);
			//ft_printf("%10s %d\n","cycle to exec pc of", tmp->player->id);
			tmp = tmp->next;
		}
		
		
		// char c;
		// c = getchar();
		if (vm->f_vus)
		{
			if (ft_event_handler(vm, wgetch(vm->w_info)))
				break;
			//if (wgetch(vm->w_info) == 27) break;
			window_right(vm->w_info, vm);
			wrefresh(vm->w_memory);
			usleep(SECOND / vm->speed);
		}
		//cbreak();
		//left_window(vm->w_memory, vm->memory);
		
		
		//nodelay(stdscr, false);
		vm->cycle_from_start++;
		//vm->current_cycle++;
		vm->current_cycle++;
	}

	//luunch winner
}