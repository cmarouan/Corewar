
#include "corewar.h"

void ft_zjmp(t_vm *vm, t_process *p)
{
    int         dir;
    uint8_t     data[2];
    t_memory    *tmp;

    if (p->carry == 0)
        return ;
    tmp = p->pc;
    PC_INCR(vm, p, 1);
    ft_getbytes(vm->memory, p->pc, 2, data);
    dir = (big_endian_to_int(data, 2) - 1) % IDX_MOD;
    if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
        ft_printf("p %4d | zjmp %d\n", p->player->id, big_endian_to_int(data, 2));
    if (vm->f_log == PC_MOV && !vm->f_vus)
        ft_print_pc_inc(0x09, tmp + 1, p->pc - tmp);
    PC_INCR(vm, p, dir);
}
