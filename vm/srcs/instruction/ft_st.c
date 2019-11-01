#include "corewar.h"

void ft_st(t_vm *vm, t_process *p)
{
    int jump_val;
    uint8_t argtype;
    uint8_t data[4];
    int result;
    int index;

    index = p->pc - vm->memory;
    if ((jump_val = ft_valide(p->opcode,vm->memory, index)) > 0)
    {
        p->cycle_to_wait = -1;
        PC_INCR(vm, p, jump_val);
        return ;
    }
    if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
        ft_printf("p %4d | st\n",p->pc_id);
    index++;
    argtype = vm->memory[MOD(index)].byte ^ (REG_CODE << SHIFT_ARG1);
    index++;
    argtype = argtype >> SHIFT_ARG2;
    result = p->reg[vm->memory[MOD(index)].byte - 1];
    index++;
    if (argtype == REG_CODE)
    {
        p->reg[vm->memory[MOD(index)].byte - 1] = result;
        index++;
    }
    else
    {
        ft_getbytes(vm->memory, vm->memory + MOD(index), 2, data);
        jump_val = index - 3 + big_endian_to_int(data, 2) % IDX_MOD;
        if (jump_val < 0)
            jump_val = MEM_SIZE + jump_val;
      //  ft_printf("cycle %d write to %d\n",vm->cycle_from_start, MOD(jump_val));
        ft_write_mem(vm, (char *)&result, 4, vm->memory + MOD(jump_val), p->player);
        index += 2;
    }
    index = index - (p->pc - vm->memory);
    PC_INCR(vm, p, index);
    p->cycle_to_wait = -1;
}