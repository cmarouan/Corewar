#include "corewar.h"

void ft_sub(t_vm *vm, t_process *p)
{
    int valide;
    int result;
    int i;

    i = 2;
    valide = ft_valide(p->pc->byte, (p->pc + 1)->byte, p->pc + 2);
    if (valide > 0)
    {
        PC_INCR(vm, p, valide);
        return ;
    }
    PC_INCR(vm, p, 2);
    //p->pc += 2;
    result = 0;
    while (i--)
    {
        if (i == 1)
            result = p->reg[p->pc->byte - 1];
        else
            result -= p->reg[p->pc->byte - 1];
        PC_INCR(vm, p, 1);
    }
    if (result == 0)
        p->carry = 1;
    else
        p->carry = 0;
    p->reg[p->pc->byte - 1] = result;
    PC_INCR(vm, p, 1);
}