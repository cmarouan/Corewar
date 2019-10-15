
#include "corewar.h"

void ft_write_mem(t_vm *vm, const char *data, int size, t_memory *mem, t_player *p)
{
    int i;

    i = size - 1;
    while (i >= 0)
    {
        if ((mem - vm->memory) >= MEM_SIZE)
			mem = mem - MEM_SIZE;
        mem->byte = data[i];
        mem->p_id = p->id;
        mem++;
        i--;
    }
}

void ft_change_pc(t_vm *vm, t_process *p, int value)
{
    int diff;

    diff = (p->pc - vm->memory) + value;
    if (diff >= 0 && diff < MEM_SIZE)
        p->pc += value;
    else if (diff >= MEM_SIZE)
        p->pc = vm->memory + diff - MEM_SIZE;
    else if (diff < 0)
        p->pc = vm->memory + MEM_SIZE + diff;
}


static int    ft_arg_tow(t_vm *vm, uint8_t *argtype, t_process *p)
{
    uint8_t data[4];
    int     jumpval;

    if (*argtype >> SHIFT_ARG2 == DIR_CODE)
    {
        ft_getbytes(vm->memory, p->pc, 2, data);
        PC_INCR(vm, p, 2);
    }else if (*argtype >> SHIFT_ARG2 == IND_CODE)
    {
        ft_getbytes(vm->memory, p->pc, 2, data);
        jumpval = big_endian_to_int(data, 2);
        ft_getbytes(vm->memory, p->pc + jumpval, 2, data);
        PC_INCR(vm, p, 2);
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

void	ft_sti(t_vm *vm, t_process *p)
{

    int reg_indx;
    uint8_t argtype;
    int val;
    t_memory *tmp;

    tmp = p->pc;
    argtype = p->pc->byte ^ (1 << SHIFT_ARG1);
    PC_INCR(vm, p, 1);
    //ft_printf("%d\n", p->pc - vm->memory);

    reg_indx = p->pc->byte;
    PC_INCR(vm, p, 1);
    val = ft_arg_tow(vm, &argtype, p);
    val += ft_arg_three(vm, &argtype, p);
    tmp = tmp + val - 1;
    val = p->reg[reg_indx - 1] * -1;
    ft_write_mem(vm, (char *)&val, 4, tmp, p->player);
}