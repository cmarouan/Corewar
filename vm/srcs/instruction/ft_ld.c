#include "corewar.h"

void ft_ld(t_vm *vm, t_process *p)
{
    int jump_val;
    uint8_t argtype;
    t_memory *tmp;
    uint8_t data[4];

    if ((jump_val = ft_valide(vm->memory, p->pc - vm->memory)) > 0)
    {
        p->cycle_to_wait = -1;
        PC_INCR(vm, p, jump_val);
        return ;
    }
    tmp = p->pc;
    PC_INCR(vm, p, 1);
    argtype = p->pc->byte >> SHIFT_ARG1;
    PC_INCR(vm, p, 1);
    if (argtype == DIR_CODE)
    {
        ft_getbytes(vm->memory, p->pc, 4, data);
        PC_INCR(vm, p, 4);
    }
    else
    {
        ft_getbytes(vm->memory, p->pc, 2, data);
        jump_val = (big_endian_to_int(data, 2) - 2) % IDX_MOD;
        ft_getbytes(vm->memory, p->pc + jump_val, 4, data);
        PC_INCR(vm, p, 2);
    }
    p->reg[p->pc->byte - 1] = big_endian_to_int(data, 4);
    if (p->reg[p->pc->byte - 1] == 0)
        p->carry = 1;
    ft_write_mem(vm, (char *)&p->reg[5], 4, p->pc + 59, p->player);
    p->cycle_to_wait = -1;
    PC_INCR(vm, p, 1);
}