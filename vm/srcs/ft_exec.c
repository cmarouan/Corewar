#include "corewar.h"

void ft_exec(t_process *p, t_vm *vm)
{
	
	if (p->cycle_to_wait <= -1)
	{
	//	ft_printf("code %p \n", p->pc);
		p->opcode = p->pc->byte;
		if (p->opcode > 0 && p->opcode <= 16)
		 	//return;
		//if (p->opcode == 0x0b) p->opcode = 2;
		p->cycle_to_wait = op_tab[p->opcode - 1].cycle - 1;
		PC_INCR(vm, p, 1);
	}else if (p->cycle_to_wait == 0)
	{
		
		//ft_printf("exec on Cycle  %d : \n",vm->cycle_from_start);	
		
		if (p->opcode <= 0 || p->opcode > 16)
			return;
		if (p->opcode == 0x0b) p->opcode = 2;
		
		if (p->opcode == 2 || p->opcode == 1)
			vm->instruction[p->opcode - 1](vm, p);
		//PC_INCR(vm, p, 1);
		//exit(0);
	}
	//ft_printf("%x\n", opcode);
	
	//ft_printf("mem start from %X\n", opcode);
	//exit(0);
	// if (opcode <= 0 || opcode > 16)
	// 	return;
	// if (opcode == 0x0b) opcode = 2;
	// if (opcode == 2 || opcode == 1)
	// 	vm->instruction[opcode - 1](vm, p);
	//else
	//	PC_INCR(vm, p, 1);
	//print_mem(vm->memory, p->pc);
	//
//	exit(0);
}