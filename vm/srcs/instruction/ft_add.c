
#include "corewar.h"

void ft_add(t_vm *vm, t_process *p)
{
    int valide;
    int r[3];
    t_memory *tmp;
    int index;

    index = p->pc - vm->memory;
    if ((valide = ft_valide(p->opcode, vm->memory, index)) > 0)
    {   
        PC_INCR(vm, p, valide);
        p->cycle_to_wait = -1;
        return ;
    }
    // if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
    //     ft_printf("p %4d | add\n",p->pc_id);
    tmp = p->pc;
    index = index + 2;
    //PC_INCR(vm, p, 2);
    r[1] = vm->memory[MOD(index)].byte - 1;
    index++;//PC_INCR(vm, p, 1);
    r[0] = vm->memory[MOD(index)].byte - 1;
    index++;//PC_INCR(vm, p, 1);
    r[2] = vm->memory[MOD(index)].byte - 1;
    p->reg[r[2]] = p->reg[r[1]] + p->reg[r[0]];
    if (p->reg[r[2]] == 0)
        p->carry = 1;
    else
        p->carry = 0;
    if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
        ft_printf("p %4d | add r%d r%d r%d\n",p->pc_id, r[1], r[0], r[2]);
    if (vm->f_log == PC_MOV && !vm->f_vus)
        ft_print_pc_inc(0x04, tmp + 1, p->pc - tmp);
    index++;
    PC_INCR(vm, p, index - (p->pc - vm->memory));
    p->cycle_to_wait = -1;
}
