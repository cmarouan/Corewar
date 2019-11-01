#include "corewar.h"

void ft_sub(t_vm *vm, t_process *p)
{
    int valide;
    int r[3];
    t_memory *tmp;
    int index;

    index = p->pc - vm->memory;
    if ((valide = ft_valide(p->opcode,vm->memory, index)) > 0)
    {
        PC_INCR(vm, p, valide);
        p->cycle_to_wait = -1;
        return ;
    }
    tmp = p->pc;
    index += 2;
   // PC_INCR(vm, p, 2);
    r[0] = vm->memory[MOD(index)].byte - 1;// p->pc->byte;
    //PC_INCR(vm, p, 1);
    index++;
    r[1] = vm->memory[MOD(index)].byte - 1;
    index++;
    r[2] = vm->memory[MOD(index)].byte - 1;
    p->reg[r[2]] = p->reg[r[0]] - p->reg[r[1]];
    if (p->reg[r[2]] == 0)
        p->carry = 1;
    else
        p->carry = 0;
    if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
        ft_printf("p %4d | sub r%d r%d r%d\n",p->pc_id, r[0], r[1], r[2]);
    if (vm->f_log == PC_MOV && !vm->f_vus)
        ft_print_pc_inc(0x05, tmp + 1, p->pc - tmp); 
    index = index - (p->pc - vm->memory);
    PC_INCR(vm, p, index + 1);
    p->cycle_to_wait = -1;
}