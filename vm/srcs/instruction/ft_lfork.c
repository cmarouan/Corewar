#include "corewar.h"


void ft_lfork(t_vm *vm, t_process *p)
{
    uint8_t data[2];
    int index;
    int jump_val;

    index = p->pc - vm->memory + 1;
    ft_getbytes(vm->memory, vm->memory + MOD(index), 2, data);
    jump_val = big_endian_to_int(data, 2);
    jump_val = index - 1 + jump_val;
    if (jump_val < 0)
        jump_val = MEM_SIZE + jump_val;
    ft_dup_process(vm, p, MOD(jump_val));
    PC_INCR(vm, p, 3);
}