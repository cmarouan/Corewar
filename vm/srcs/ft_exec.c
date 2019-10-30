#include "corewar.h"

void ft_exec(t_process *p, t_vm *vm)
{

	if (p->cycle_to_wait <= -1)
	{
	//	ft_printf("code %p \n", p->pc);
		
		
		if (p->pc->byte > 0 && p->pc->byte <= 16)
		{
			p->opcode = p->pc->byte;
			p->cycle_to_wait = op_tab[p->opcode - 1].cycle - 1;
			//ft_printf("%s\n", op_tab[p->opcode - 1].name);
		}
		else
			PC_INCR(vm, p, 1);


		
		if (p->oldindex == -1)
			ft_move_pc(p, vm);
		
	}
    else if (p->cycle_to_wait == 0)
	{
		
		//ft_printf("exec on Cycle  %d : \n",vm->cycle_from_start);	
		// Temp instruvtion : ????/
		//if (p->opcode == 0x0b) p->opcode = 2;
		// Temp instruction : ????/
		
		if (p->opcode >= 1 && p->opcode <= 15)
		{
			//ft_printf("cycle %d Oper  %s\n",vm->cycle_from_start, op_tab[p->opcode - 1].name);
			// if (vm->cycle_from_start >= 5440 && vm->cycle_from_start <= 5450)
			// 	ft_printf("op name : %s\n", op_tab[p->pc->byte - 1].name);
			vm->instruction[p->opcode - 1](vm, p);
			
		}
		// Temp instruction : ????/
		else
			PC_INCR(vm, p, 1);
		
		//p->cycle_to_wait = -1;
		// Temp instruction : ????/
		//exit(0);
	}
}