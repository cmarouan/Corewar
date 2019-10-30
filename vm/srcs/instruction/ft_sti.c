
#include "corewar.h"



static int    ft_arg_two(t_vm *vm, uint8_t *argtype, t_process *p, int *index)
{
    uint8_t data[4];
    int     jump_val;

    if (*argtype >> SHIFT_ARG2 == DIR_CODE)
    {
        ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
        *index = *index + 2;
        //PC_INCR(vm, p, 2);
    }else if (*argtype >> SHIFT_ARG2 == IND_CODE)
    {
        ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
        jump_val = p->pc - vm->memory + big_endian_to_int(data, 2) % IDX_MOD;
        if (jump_val < 0)
            jump_val = MEM_SIZE + jump_val;
        ft_getbytes(vm->memory, vm->memory + MOD(jump_val), 4, data);
        //PC_INCR(vm, p, 2);
        *index = *index + 2;
        *argtype ^= (IND_CODE << SHIFT_ARG2);
        return (big_endian_to_int(data, 4));
    }else
    {
        jump_val = vm->memory[*MOD(index)].byte - 1;
        //PC_INCR(vm, p, 1);
        *index = *index + 1;
        *argtype ^= (REG_CODE << SHIFT_ARG2);
        return (p->reg[jump_val]);
    }
    *argtype ^= (DIR_CODE << SHIFT_ARG2);
    return (big_endian_to_int(data, 2));
}

static int  ft_arg_three(t_vm *vm, uint8_t *argtype, t_process *p, int *index)
{
    uint8_t data[4];
    int reg_index;

    if (*argtype >> SHIFT_ARG3 == DIR_CODE)
    {
        ft_getbytes(vm->memory, vm->memory + (*MOD(index)), 2, data);
        //PC_INCR(vm, p, 2);
        *index = *index + 2;
        return (big_endian_to_int(data, 2));
    }else
    {
        //PC_INCR(vm, p, 1);
        //*index = *index + 1;
        reg_index = vm->memory[*MOD(index)].byte - 1;
        *index = *index + 1;
        return (p->reg[reg_index]);
    }
}

// static void ft_checklog(t_vm *vm, t_process *p, int *val, t_memory *tmp)
// {
//      if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
//         ft_printf("p %4d | sti r%d %d %d\n %7s -> store %d to %d\n",
//         p->player->id, val[2], val[0], val[1], "|", p->reg[val[2] - 1] * -1,
//         val[0] + val[1]);
//     if (vm->f_log == PC_MOV && !vm->f_vus)
//         ft_print_pc_inc(0x0b, tmp, p->pc - tmp);
// }

void	ft_sti(t_vm *vm, t_process *p)
{
    uint8_t argtype;
    int val[3];
   // t_memory *tmp;
    //t_memory *tmp2;
    int index;
    
    index = p->pc - vm->memory;
    if ((val[2] = ft_valide(vm->memory, index)) > 0)
    {
        PC_INCR(vm, p, val[2]);
        p->cycle_to_wait = -1;
        return;
    }

   // tmp = p->pc;
    //PC_INCR(vm, p, 1);
    index++;
    
    //tmp2 = p->pc;
    argtype = vm->memory[MOD(index)].byte ^ (REG_CODE << SHIFT_ARG1);

    //PC_INCR(vm, p, 1);
    // if (vm->cycle_from_start >= 2814 && vm->cycle_from_start <= 2850)
    // {
    //     ft_printf("|%.8b|\n", vm->memory[MOD(index)].byte);
    // }
    index++;
    val[2] = vm->memory[MOD(index)].byte;
    
    
    //PC_INCR(vm, p, 1);
    index++;

    val[0] = ft_arg_two(vm, &argtype, p, &index);
    
    val[1] = ft_arg_three(vm, &argtype, p, &index);
   
   // ft_printf("%d %d\n", val[0], val[1]);
   
    
    val[1] = (val[0] + val[1]) % IDX_MOD;
    // ft_printf("%d \n", val[1]);
    // exit(0);
    //ft_checklog(vm, p, val, tmp2);
    
    val[1] =  (p->pc - vm->memory) + val[1];
    if (val[1] < 0)
        val[1] = MEM_SIZE + val[1];
    val[0] = p->reg[val[2] - 1];
    // if (vm->cycle_from_start >= 2814 && vm->cycle_from_start <= 2850)
    // {
    //     printf("cycle = %d   arg2 = %d | arg3 = %d\n", vm->cycle_from_start, val[0],val[1]);
    //     ft_printf("p %4d | sti r%d %d %d\n %7s -> store %d to %d\n",
    //     p->player->id, val[2], val[0], val[1], "|", p->reg[val[2] - 1] * -1,
    //     (val[0] + val[1])%IDX_MOD);
    // }
   // ft_printf("cycle %d write to %d\n",vm->cycle_from_start, MOD(val[1]));
    ft_write_mem(vm, (char *)&val[0], 4, vm->memory + MOD(val[1]), p->player);
    p->cycle_to_wait = -1;
    index = (p->pc - vm->memory) - index;
    if (index < 0)
        index *= -1;
    PC_INCR(vm, p, index);
}