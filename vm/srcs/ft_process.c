/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 23:02:28 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/04 00:02:58 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process		*ft_add_pc(t_vm *vm, int index, t_player *player)
{
	t_process	*new;

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
	new->next = NULL;
	new->live_declare = 0;
	new->cycle_to_wait = -1;
	if (!vm->process)
		return (new);
	new->next = vm->process;
	return (new);
}

void			ft_dup_process(t_vm *vm, t_process *p, int index)
{
	t_process	*new;

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
	new->cycle_to_wait = p->cycle_to_wait;
	new->opcode = -1;
	new->oldindex = p->oldindex;
	new->live_declare = p->live_declare;
	new->next = vm->process;
	vm->process = new;
	new->pc_id = ++vm->pc_ids;
}

void			ft_free_process(t_process *p)
{
	free(p->reg);
	free(p);
}

t_process		*ft_kill_process(t_vm *vm)
{
	t_process	*head;
	t_process	*tmp;
	t_process	*prev;

	head = NULL;
	tmp = vm->process;
	prev = NULL;
	while (tmp)
		if (!tmp->live_declare)
		{
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
		}
		else
		{
			head = !head ? tmp : head;
			tmp->live_declare = 0;
			prev = tmp;
			tmp = tmp->next;
		}
	return (head);
}
