/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 22:53:41 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/03 23:09:32 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_check_vm(t_vm *vm)
{
	if (vm->current_cycle == 1)
	{
		ft_check(vm);
		if (vm->f_vus)
			window_right(vm->w_info, vm);
		vm->current_cycle = vm->cycle_to_die;
	}
	else
		vm->current_cycle--;
}

static void	ft_exec_process(t_vm *vm)
{
	t_process *tmp;

	tmp = vm->process;
	while (tmp)
	{
		if (tmp->cycle_to_wait <= 0)
			ft_exec(tmp, vm);
		if (tmp->cycle_to_wait > -1)
			tmp->cycle_to_wait--;
		if (vm->f_vus)
			window_right(vm->w_info, vm);
		tmp = tmp->next;
	}
	ft_check_vm(vm);
}

static int	ft_vis_control(t_vm *vm)
{
	if (vm->f_vus)
	{
		if (ft_event_handler(vm, wgetch(vm->w_info)) == -1)
			return (1);
		window_right(vm->w_info, vm);
		wrefresh(vm->w_memory);
		usleep(SECOND / vm->speed);
	}
	return (0);
}

int			ft_start(t_vm *vm)
{
	char c;

	vm->current_cycle = vm->cycle_to_die;
	while (vm->current_cycle > 0)
	{
		if (ft_vis_control(vm))
			break ;
		vm->cycle_from_start++;
		ft_exec_process(vm);
		if (!vm->process)
			break ;
		if (vm->f_dump > 0 && vm->f_dump == vm->cycle_from_start && !vm->f_vus)
		{
			print_mem(vm->memory);
			ft_free_vm(vm);
			return (-1);
		}
		if (vm->f_show > 0 && !(vm->cycle_from_start % vm->f_show)
				&& !vm->f_vus)
		{
			print_mem(vm->memory);
			read(0, &c, 1);
		}
	}
	return (1);
}
