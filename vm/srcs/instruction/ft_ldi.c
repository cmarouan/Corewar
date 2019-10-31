
#include "corewar.h"

static int    ft_arg_one(t_vm *vm, uint8_t *argtype, t_process *p, int *index)
{
    uint8_t data[4];
    int     jump_val;
    
    if (*argtype >> SHIFT_ARG1 == DIR_CODE)
    {
        ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
        *index += 2;
        
    }else if (*argtype >> SHIFT_ARG1 == IND_CODE)
    {
        ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
        jump_val = p->pc - vm->memory + (big_endian_to_int(data, 2) % IDX_MOD);
        if (jump_val < 0)
            jump_val = MEM_SIZE + jump_val;
        ft_getbytes(vm->memory, vm->memory + MOD(jump_val), 4, data);
        *index += 2;
        *argtype ^= (IND_CODE << SHIFT_ARG1);
        return (big_endian_to_int(data, 4));
    }else
    {
        jump_val = vm->memory[*MOD(index)].byte - 1;
        *index = *index + 1;
        *argtype ^= (REG_CODE << SHIFT_ARG1);
        return (p->reg[jump_val]);
    }
    *argtype ^= (DIR_CODE << SHIFT_ARG1);
    return (big_endian_to_int(data, 2));
}

static int    ft_arg_two(t_vm *vm, uint8_t *argtype, t_process *p, int *index)
{
    uint8_t data[4];
    int     jump_val;
  
    if (*argtype >> SHIFT_ARG2 == DIR_CODE)
    {
        ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
        *index += 2;
    }
    else
    {
        jump_val = vm->memory[*MOD(index)].byte - 1;
        *index = *index + 1;
        *argtype ^= (REG_CODE << SHIFT_ARG2);
        return (p->reg[jump_val]);
    }
    *argtype ^= (DIR_CODE << SHIFT_ARG2);
    return (big_endian_to_int(data, 2));
}

void	ft_ldi(t_vm *vm, t_process *p)
{
    uint8_t argtype;
    int val[3];
    uint8_t data[4];
    int index;

    index = p->pc - vm->memory;
    if ((val[2] = ft_valide(vm->memory, index)) > 0)
    {
        PC_INCR(vm, p, val[2]);
        p->cycle_to_wait = -1;
        return;
    }
    if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
        ft_printf("p %4d | ldi\n | load from \n",p->pc_id);
    index++;
    argtype = vm->memory[MOD(index)].byte;
    index++;
    val[0] = ft_arg_one(vm, &argtype, p, &index);
    val[1] = ft_arg_two(vm, &argtype, p, &index);
    val[2] = p->pc - vm->memory +  ((val[0] + val[1]) % IDX_MOD);
    if (val[2] < 0)
        val[2] = MEM_SIZE + val[2];
    ft_getbytes(vm->memory, vm->memory + MOD(val[2]), 4, data);
    p->reg[vm->memory[MOD(index)].byte - 1] = big_endian_to_int(data, 4);
    index++;
    p->cycle_to_wait = -1;
    index = (p->pc - vm->memory) - index;
    if (index < 0)
        index *= -1;
    PC_INCR(vm, p, index);
}