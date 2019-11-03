/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_vm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:47:38 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/03 16:48:54 by cmarouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_free_vm(t_vm *vm)
{
	t_process	*tmp;
	t_process	*prev;
	int			i;

	i = 0;
	tmp = vm->process;
	while (i < vm->player_c)
	{
		free(vm->players[i].code);
		i++;
	}
	free(vm->players);
	free(vm->ids);
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		free(prev->reg);
		free(prev);
	}
	free(vm->memory);
	free(vm);
}
