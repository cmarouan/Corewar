#include "corewar.h"

void ft_exec(t_process *p, t_vm *vm)
{
	
	if (p->cycle_to_wait <= -1)
	{
	//	ft_printf("code %p \n", p->pc);
		p->opcode = p->pc->byte;
		if (p->opcode > 0 && p->opcode <= 16)
		    p->cycle_to_wait = op_tab[p->opcode - 1].cycle - 1;
		else
			PC_INCR(vm, p, 1);
		if (p->oldindex == -1)
			ft_move_pc(p, vm);
		
	}
        else if (p->cycle_to_wait == 0)
	{
		
		//ft_printf("exec on Cycle  %d : \n",vm->cycle_from_start);	
		// Temp instruvtion : ????/
		if (p->opcode == 0x0b) p->opcode = 2;
		// Temp instruction : ????/
		
		if (p->opcode == 2 || p->opcode == 1)
			vm->instruction[p->opcode - 1](vm, p);
		// Temp instruction : ????/
		else
			PC_INCR(vm, p, 1);
		// Temp instruction : ????/
		//exit(0);
	}
}