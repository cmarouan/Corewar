#include "corewar.h"


t_process *ft_add_pc(t_vm *vm, t_memory *mem, t_player *player)
{
    t_process *new;
    t_process *tmp;
    t_process *p;

    p = vm->process;
   // ft_printf("####%#p####\n", p);
    new = (t_process *)malloc(sizeof(t_process));
    new->reg = (int *)malloc(REG_SIZE * REG_NUMBER);
    ft_memset(new->reg, 0, REG_NUMBER);
    new->reg[0] = player->id;
    new->pc = mem;
    new->oldindex = -1;
    new->next = NULL;
    new->player = player;
    new->carry = 0;
    new->next = NULL;;
    new->cycle_to_wait = -1;
    if (!p)
        return (new);
    tmp = p;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
  //  new->next = p;
    return (p);
}