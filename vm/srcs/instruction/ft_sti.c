
#include "corewar.h"

static int    ft_arg_tow(t_vm *vm, uint8_t *argtype, t_process *p)
{
    uint8_t data[4];
    int     jump_val;

    if (*argtype >> SHIFT_ARG2 == DIR_CODE)
    {
        ft_getbytes(vm->memory, p->pc, 2, data);
        PC_INCR(vm, p, 2);
    }else if (*argtype >> SHIFT_ARG2 == IND_CODE)
    {
        ft_getbytes(vm->memory, p->pc, 2, data);
        jump_val = (big_endian_to_int(data, 2) - 3) % IDX_MOD;
        ft_getbytes(vm->memory, p->pc + jump_val, 4, data);
        PC_INCR(vm, p, 2);
        return (big_endian_to_int(data, 4));
    }else
    {
        PC_INCR(vm, p, 1);
        *argtype ^= (1 << SHIFT_ARG2);
        return (p->reg[p->pc->byte - 1]);
    }
    *argtype ^= ((*argtype >> SHIFT_ARG2) << SHIFT_ARG2);
    return (big_endian_to_int(data, 2));
}

static int  ft_arg_three(t_vm *vm, uint8_t *argtype, t_process *p)
{
    uint8_t data[4];

    if (*argtype >> SHIFT_ARG3 == DIR_CODE)
    {
        ft_getbytes(vm->memory, p->pc, 2, data);
        PC_INCR(vm, p, 2);
        return (big_endian_to_int(data, 2));
    }else
    {
        PC_INCR(vm, p, 1);
        return (p->reg[p->pc->byte - 1]);
    }
}

static void ft_checklog(t_vm *vm, t_process *p, int *val, t_memory *tmp)
{
     if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
        ft_printf("p %4d | sti r%d %d %d\n %7s -> store %d to %d\n",
        p->player->id, val[2], val[0], val[1], "|", p->reg[val[2] - 1] * -1,
        val[0] + val[1]);
    if (vm->f_log == PC_MOV && !vm->f_vus)
        ft_print_pc_inc(0x0b, tmp, p->pc - tmp);
}

void	ft_sti(t_vm *vm, t_process *p)
{
    uint8_t argtype;
    int val[3];
    t_memory *tmp;
    t_memory *tmp2;

    if ((val[2] = ft_valide(vm->memory, p->pc - vm->memory)) > 0)
    {
        PC_INCR(vm, p, val[2]);
        p->cycle_to_wait = -1;
        return;
    }
    tmp = p->pc;
    PC_INCR(vm, p, 1);
    tmp2 = p->pc;
    argtype = p->pc->byte ^ (T_REG << SHIFT_ARG1);
    PC_INCR(vm, p, 1);
    val[2] = p->pc->byte;
    PC_INCR(vm, p, 1);
    val[0] = ft_arg_tow(vm, &argtype, p);
    val[1] = ft_arg_three(vm, &argtype, p);
    tmp = tmp + (val[0] + val[1])%IDX_MOD;
    ft_checklog(vm, p, val, tmp2);
    val[0] = p->reg[val[2] - 1] * -1;
    ft_write_mem(vm, (char *)&val[0], 4, tmp, p->player);
    p->cycle_to_wait = -1;
}