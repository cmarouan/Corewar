
#include "corewar.h"

void ft_zjmp(t_vm *vm, t_process *p)
{
    int         dir;
    uint8_t     data[2];
    t_memory    *tmp;
    int index;


   
    if (p->carry == 0)
    {
        p->cycle_to_wait = -1;
        PC_INCR(vm, p, 3);
        return ;
    }
    index = p->pc - vm->memory;
    tmp = p->pc;
    //PC_INCR(vm, p, 1);
    index++;
    ft_getbytes(vm->memory, vm->memory + MOD(index), 2, data);
    dir = big_endian_to_int(data, 2) % IDX_MOD;
   // printf("cycle %d, zjmp to %d\n", vm->cycle_from_start, dir);
    if (vm->f_log == INSTRUCTION_LOG && !vm->f_vus)
        ft_printf("p %4d | zjmp %d OK\n", p->player->id, big_endian_to_int(data, 2));
    if (vm->f_log == PC_MOV && !vm->f_vus)
        ft_print_pc_inc(0x09, tmp + 1, p->pc - tmp);
    p->cycle_to_wait = -1;
    //p->pc = vm->memory + MOD(dir);
   // ft_printf("%d\n", p->pc - vm->memory);
    PC_INCR(vm, p, dir);
    //exit(0);
}
