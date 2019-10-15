
#include "corewar.h"

void ft_getbytes(t_memory *mem, t_memory *pc, int size, uint8_t data[])
{
	int		i;

	i = 0;
	while (i < size)
	{
		if ((pc - mem) >= MEM_SIZE)
			pc = pc - MEM_SIZE;
		data[i] = pc->byte;
		pc++;
		i++;
	}
}

void	ft_live(t_vm *vm, t_process *p)
{
	uint8_t data[4];
	int		ind;
	int		i;

	
	ft_getbytes(vm->memory, p->pc, 4, data);
	PC_INCR(vm, p, 4);
	ind = -1 * big_endian_to_int(data, 4);
	i = 0;
	while (i < vm->player_c && vm->players[i].id != ind)
		i++;
	
	if (i == vm->player_c)
		return;
	vm->nbr_live++;
    vm->current_cycle += op_tab[0].cycle;
	vm->players[i].last_live = vm->current_cycle;
    vm->players[i].live_in_current_cycle++;
    if (vm->f_log == 1)
	    ft_printf("A process shows that player %d (%s) is alive\n",
                 vm->players[i].id, vm->players[i].prog_name);
}