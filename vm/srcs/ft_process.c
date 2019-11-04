/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 23:02:28 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/04 13:46:11 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process		*ft_add_pc(t_vm *vm, int index, t_player *player)
{
	t_process	*new;

	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		ft_outerr(errno, vm);
	if (!(new->reg = (int *)ft_memalloc(REG_SIZE * REG_NUMBER)))
		ft_outerr(errno, vm);
	new->reg[0] = player->id * -1;
	new->pc = vm->memory + index;
	new->oldindex = -1;
	new->next = NULL;
	new->player = player;
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
	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		ft_outerr(errno, vm);
	if (!(new->reg = (int *)ft_memalloc(REG_SIZE * REG_NUMBER)))
		ft_outerr(errno, vm);
	ft_memcpy(new->reg, p->reg, REG_SIZE * REG_NUMBER);
	new->pc = vm->memory + index;
	new->oldindex = -1;
	new->player = p->player;
	new->carry = p->carry;
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

static void		ft_death_log(t_vm *vm, t_process *tmp)
{
	if (!vm->f_vus && vm->f_log == DEATHS_LOG)
		ft_printf("Process %d killed on cycle %d\n",
				tmp->pc_id, vm->cycle_from_start);
}

t_process		*ft_kill_process(t_vm *vm, t_process *head, t_process *tmp,
				t_process *prev)
{
	while (tmp)
		if (!tmp->live_declare)
		{
			ft_death_log(vm, tmp);
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
