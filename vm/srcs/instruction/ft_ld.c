#include "corewar.h"

void ft_ld(t_vm *vm, t_process *p)
{
    int jump_val;
    uint8_t argtype;
    t_memory *tmp;
    uint8_t data[4];
    int index;

    index = p->pc - vm->memory;
    if ((jump_val = ft_valide(vm->memory, index)) > 0)
    {
        p->cycle_to_wait = -1;
        PC_INCR(vm, p, jump_val);
        return ;
    }
    tmp = p->pc;
  //  PC_INCR(vm, p, 1);
    index++;
    argtype = vm->memory[MOD(index)].byte >> SHIFT_ARG1;
    //PC_INCR(vm, p, 1);
    index++;
    if (argtype == DIR_CODE)
    {
        ft_getbytes(vm->memory, vm->memory + (MOD(index)), 4, data);
        index += 4;
        //PC_INCR(vm, p, 4);
    }
    else
    {
        ft_getbytes(vm->memory, vm->memory + (MOD(index)), 2, data);
        jump_val = big_endian_to_int(data, 2) % IDX_MOD;
        ft_getbytes(vm->memory, p->pc + jump_val, 4, data);
        index += 2;
        //PC_INCR(vm, p, 2);
    }
    p->reg[vm->memory[MOD(index)].byte - 1] = big_endian_to_int(data, 4);
    if (p->reg[vm->memory[MOD(index)].byte - 1] == 0)
        p->carry = 1;
   // ft_write_mem(vm, (char *)&p->reg[5], 4, p->pc + 59, p->player);
    p->cycle_to_wait = -1;
    index = (p->pc - vm->memory) - index;
    if (index < 0)
        index *= -1;
    PC_INCR(vm, p, (index + 1));
}