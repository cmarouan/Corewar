
#include "corewar.h"

static int    ft_arg_one(t_vm *vm, uint8_t *argtype, t_process *p, int *index)
{
    uint8_t data[4];
    int     jump_val;
    
    if (*argtype >> SHIFT_ARG1 == DIR_CODE)
    {
        ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 4, data);
        *index = *index + 4;
        
    }else if (*argtype >> SHIFT_ARG1 == IND_CODE)
    {
        ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
        jump_val = p->pc - vm->memory + big_endian_to_int(data, 2) % IDX_MOD;
        if (jump_val < 0)
            jump_val = MEM_SIZE + jump_val;
        ft_getbytes(vm->memory, vm->memory + MOD(jump_val), 4, data);
        *index = *index + 2;
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
    return (big_endian_to_int(data, 4));
}

static int    ft_arg_two(t_vm *vm, uint8_t *argtype, t_process *p, int *index)
{
    uint8_t data[4];
    int     jump_val;
  
    if (*argtype >> SHIFT_ARG2 == DIR_CODE)
    {
        ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 4, data);
        *index = *index + 4;
    }else if (*argtype >> SHIFT_ARG2 == IND_CODE)
    {
        ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
        jump_val = p->pc - vm->memory + big_endian_to_int(data, 2) % IDX_MOD;
        if (jump_val < 0)
            jump_val = MEM_SIZE + jump_val;
        ft_getbytes(vm->memory, vm->memory + MOD(jump_val), 4, data);
        *index = *index + 2;
        *argtype ^= (IND_CODE << SHIFT_ARG2);
        return (big_endian_to_int(data, 4));
    }else
    {
        jump_val = vm->memory[*MOD(index)].byte - 1;
        *index = *index + 1;
        *argtype ^= (REG_CODE << SHIFT_ARG2);
        return (p->reg[jump_val]);
    }
    *argtype ^= (DIR_CODE << SHIFT_ARG2);
    return (big_endian_to_int(data, 4));
}

//  static void ft_checklog(t_vm *vm, t_process *p, int *val)
// {
//      if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
//         ft_printf("p %4d | and r%d %d %d\n %7s -> store %d to %d\n",
//         p->player->id, val[2], val[0], val[1], "|", p->reg[val[2] - 1] * -1,
//         val[0] + val[1]);
//     if (vm->f_log == PC_MOV && !vm->f_vus)
//         ft_print_pc_inc(0x0b, tmp, p->pc - tmp);
// }

void	ft_and(t_vm *vm, t_process *p)
{
    uint8_t argtype;
    int val[3];
    int index;

    index = p->pc - vm->memory;
    if ((val[2] = ft_valide(p->opcode, vm->memory, index)) > 0)
    {
        PC_INCR(vm, p, val[2]);
        p->cycle_to_wait = -1;
        return;
    }
    if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
        ft_printf("p %4d | Xor\n",p->pc_id);
    index++;
    argtype = vm->memory[MOD(index)].byte;
    index++;
    val[0] = ft_arg_one(vm, &argtype, p, &index);
    val[1] = ft_arg_two(vm, &argtype, p, &index);
    p->reg[vm->memory[MOD(index)].byte - 1] = val[0] & val[1];
    if (p->reg[vm->memory[MOD(index)].byte - 1] == 0)
        p->carry = 1;
    else
        p->carry = 0;
    p->cycle_to_wait = -1;
    index++;
    index = index - (p->pc - vm->memory);
    PC_INCR(vm, p, index);
}