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

    new->kill = 1;
vm->pc_count++;
    new->carry = 0;
    new->opcode = -1;
    new->pc_id = ++vm->pc_ids;
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

    new->kill = 1;
    vm->pc_count++;
    //new->opcode = -1;
    new->cycle_to_wait = p->cycle_to_wait;
    new->opcode = -1;
    new->oldindex = p->oldindex;
    new->live_declare = p->live_declare;
    new->next = vm->process;
    vm->process = new;
    new->pc_id = ++vm->pc_ids;
}


void    ft_free_process(t_process *p)
{
    free(p->reg);
    free(p);
}


t_process   *ft_kill_process(t_vm *vm)
{
    t_process *head;
    t_process *tmp;

    head = vm->process;
    tmp = vm->process;
    while (tmp)
    {
        //printf("|%d|\n", tmp->live_declare);
        if (tmp->live_declare == 0 && tmp->kill)
        {
            tmp->kill = 0;
            vm->pc_count--;
            //ft_printf("cycle : %d, kill pc %d \n",vm->cycle_from_start, tmp->pc_id);
        }else
            tmp->live_declare = 0;
        tmp = tmp->next;
    }
    return head;
}

/*
t_process   *ft_kill_process(t_vm *vm)
{
    t_process *head;
    t_process *tmp;
    t_process *prev;

    head = NULL;
    tmp = vm->process;
    prev = NULL;
    while (tmp)
    {
        if (!tmp->live_declare)
        {

            ft_printf("cycle : %d, kill pc %d \n",vm->cycle_from_start, tmp->pc_id);
            vm->pc_count--;
            if (prev == NULL)
            {
                prev = tmp;
                tmp = tmp->next;
                ft_free_process(prev);
                prev = NULL;
                continue;
            }
            prev->next = tmp->next;
            ft_free_process(tmp);
            tmp = prev->next;
        }else
        {
            if (!head)
                head = tmp;
            tmp->live_declare = 0;
            prev = tmp;
            tmp = tmp->next;
        }
    }
   return (head);

}
*/