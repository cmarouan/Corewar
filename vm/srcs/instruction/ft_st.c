#include "corewar.h"

void ft_st(t_vm *vm, t_process *p)
{
    int jump_val;
    uint8_t argtype;
    t_memory *tmp;
    uint8_t data[4];
    int result;

    if ((jump_val = ft_valide(vm->memory, p->pc - vm->memory)) > 0)
    {
        p->cycle_to_wait = -1;
        PC_INCR(vm, p, jump_val);
        return ;
    }
    tmp = p->pc;
    PC_INCR(vm, p, 1);
    argtype = p->pc->byte ^ (REG_CODE << SHIFT_ARG1);
    PC_INCR(vm, p, 1);
    argtype = argtype >> SHIFT_ARG2;
    result = p->reg[p->pc->byte - 1];
    PC_INCR(vm, p, 1);
    if (argtype == REG_CODE)
    {
        p->reg[p->pc->byte - 1] = result;
        PC_INCR(vm, p, 1);
    }
    else
    {
        ft_getbytes(vm->memory, p->pc, 2, data);
        jump_val = (big_endian_to_int(data, 2) - 3) % IDX_MOD;
      //  ft_printf("\n##%x##", big_endian_to_int(data, 2));
       // exit(0);
        ft_write_mem(vm, (char *)&result, 4, p->pc + jump_val, p->player);
        //ft_getbytes(vm->memory, p->pc + jump_val, 4, data);
        PC_INCR(vm, p, 2);
    }
    p->cycle_to_wait = -1;
}