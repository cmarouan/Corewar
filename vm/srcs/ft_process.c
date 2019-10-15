#include "corewar.h"


t_process *ft_add_pc(t_process *p, t_memory *mem, t_player *player)
{
    t_process *new;
    t_process *tmp;

    new = (t_process *)malloc(sizeof(t_process));
    new->reg = malloc(REG_SIZE * REG_NUMBER);
    new->reg[0] = player->id;
    new->pc = mem;
    new->next = NULL;
    new->player = player;
    new->next = new;
    if (!p)
        return (new);
    tmp = p->next;
    while (tmp->next != p)
        tmp = tmp->next;
    tmp->next = new;
    new->next = p;
    return (p);
}