/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:37:02 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/03 16:38:03 by cmarouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_check(t_vm *vm)
{
	int	i;

	i = 0;
	vm->nbr_of_check++;
	if (vm->nbr_live >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->nbr_of_check = 0;
	}
	else if (vm->nbr_of_check >= MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->nbr_of_check = 0;
	}
	vm->nbr_live = 0;
	while (i < vm->player_c)
	{
		vm->players[i].live_in_current_period = 0;
		i++;
	}
	vm->process = ft_kill_process(vm);
	if (vm->f_vus)
		wrefresh(vm->w_info);
}
