#include "corewar.h"


t_process *ft_add_pc(t_vm *vm,int index, t_player *player)
{
    t_process *new;
    t_process *tmp;
    t_process *p;

    p = vm->process;
   // ft_printf("####%#p####\n", p);
    new = (t_process *)malloc(sizeof(t_process));
    new->reg = (int *)malloc(REG_SIZE * REG_NUMBER);
    ft_memset(new->reg, 0, REG_SIZE * REG_NUMBER);
    new->reg[0] = player->id * -1;
    new->pc = vm->memory + index;
    new->oldindex = -1;
    new->next = NULL;
    new->player = player;
    new->carry = 0;
    new->opcode = -1;
    vm->pc_count++;
    new->pc_id = vm->pc_count;
    new->next = NULL;;
    new->live_declare = 0;
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

void ft_dup_process(t_vm *vm, t_process *p, int index)
{
    t_process *new;
   // p = vm->process;
   // ft_printf("####%#p####\n", p);
   if (!p)
        return ;
    new = (t_process *)malloc(sizeof(t_process));
    new->reg = (int *)malloc(REG_SIZE * REG_NUMBER);
    ft_memcpy(new->reg, p->reg, REG_SIZE * REG_NUMBER);
    new->pc = vm->memory + index;
    new->oldindex = -1;
    new->player = p->player;
    new->carry = p->carry;
    new->cycle_to_wait = -1;
    //new->opcode = -1;
    new->oldindex = p->oldindex;
    new->live_declare = p->live_declare;
    new->next = vm->process;
    vm->process = new;
    vm->pc_count++;
    new->pc_id = vm->pc_count;
}
void    ft_kill_process(t_vm *vm, int pc_id)
{
    t_process *tmp_1;
    t_process *tmp_2;

    tmp_1 = vm->process;
    tmp_2 = tmp_1;
    while (tmp_1)
    {
        if (tmp_1->pc_id == pc_id)
            break;
        tmp_2 = tmp_1;
        tmp_1 = tmp_1->next;
    }
    tmp_2->next = tmp_1->next;
    free(tmp_1->reg);
    free(tmp_1);
}
