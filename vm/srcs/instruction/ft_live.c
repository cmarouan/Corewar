
#include "corewar.h"

void	ft_live(t_vm *vm, t_process *p)
{
	uint8_t data[4];
	int		ind;
	int		i;
	t_memory *tmp;

	vm->nbr_live++;
	//mvwprintw(vm->w_info, 9, 5, "Nbr of lives : %.10d/%-20d", vm->nbr_live, NBR_LIVE);
	//wrefresh(vm->w_info);
	//printf("%d\n", vm->nbr_live);
	p->live_declare++;
	p->cycle_to_wait = -1;
	PC_INCR(vm, p, 1);
	tmp = p->pc;
	ft_getbytes(vm->memory, p->pc, 4, data);
	PC_INCR(vm, p, 4);
	ind = -1 * big_endian_to_int(data, 4);
	i = 0;
	
	if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
		ft_printf("P %4d | live %d\n",
                 p->pc_id, -1 * ind);
	
	while (i < vm->player_c && vm->players[i].id != ind)
		i++;
	//ft_printf("%d\n", vm->cycle_from_start);
	if (i == vm->player_c)
		return;
	//ft_printf("Cycle  %d : \n",vm->cycle_from_start);
	if (vm->f_log == LIVES_LOG && !vm->f_vus)
	    ft_printf("A process shows that player %d (%s) is alive at %d\n",
                 vm->players[i].id, vm->players[i].prog_name, vm->cycle_from_start);
	vm->players[i].last_live = vm->cycle_from_start;
    vm->players[i].live_in_current_period++;
    
	if (vm->f_log == PC_MOV)
		ft_print_pc_inc(1, tmp, p->pc - tmp);
	

}