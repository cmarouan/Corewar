#include "corewar.h"

void ft_lld(t_vm *vm, t_process *p)
{
    int jump_val;
    uint8_t argtype;
    t_memory *tmp;
    uint8_t data[4];
    int index;

    index = p->pc - vm->memory;
    if ((jump_val = ft_valide(p->opcode,vm->memory, index)) > 0)
    {
        p->cycle_to_wait = -1;
        PC_INCR(vm, p, jump_val);
        return ;
    }
    if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
        ft_printf("p %4d | lld\n",p->pc_id);
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
        jump_val = p->pc - vm->memory + big_endian_to_int(data, 2);
        if (jump_val < 0)
            jump_val = MEM_SIZE + jump_val;
        ft_getbytes(vm->memory, vm->memory + MOD(jump_val), 4, data);
        index += 2;
        //PC_INCR(vm, p, 2);
    }
    p->reg[vm->memory[MOD(index)].byte - 1] = big_endian_to_int(data, 4);
    if (p->reg[vm->memory[MOD(index)].byte - 1] == 0)
        p->carry = 1;
    else
        p->carry = 0;
   // ft_write_mem(vm, (char *)&p->reg[5], 4, p->pc + 59, p->player);
    p->cycle_to_wait = -1;
    index = index - (p->pc - vm->memory);
    PC_INCR(vm, p, index);
}