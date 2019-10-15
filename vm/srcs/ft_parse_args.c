/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:44:26 by kmoussai          #+#    #+#             */
/*   Updated: 2019/10/15 20:25:59 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		ft_check_ext(char *str)
{
	int index;

	//ft_printf("arg to check : %s\n", str);
	index = ft_strlen(str) - 4;
	return (index && str && !ft_strcmp(".cor", str + index));
}

static void		ft_check_ids(t_vm *vm)
{
	int i;
	int index;

	i = -1;
	index = 1;
	ft_memset(vm->ids, 0, MAX_PLAYERS + 1);
	while (++i < vm->player_c)
		if (vm->players[i].id_set && vm->players[i].id > 0
				&& vm->players[i].id <= vm->player_c
				&& !vm->ids[vm->players[i].id])
			vm->ids[vm->players[i].id] = 1;
		else if (vm->players[i].id_set && (vm->players[i].id <= 0
					|| vm->players[i].id > vm->player_c
					|| vm->ids[vm->players[i].id]))
			ft_usage();
	i = -1;
	while (++i < vm->player_c)
		if (!vm->players[i].id_set)
		{
			while (vm->ids[index])
				index++;
			vm->players[i].id = index++;
		}
}

static int		ft_check_flag(t_vm *vm, int i, char **argv)
{
	vm->players[vm->player_c].id_set = 0;
	if ((!ft_strcmp(argv[i], "-dump") || !ft_strcmp(argv[i], "-d"))
			&& argv[i + 1])
		vm->f_dump = ft_atoi(argv[++i]);
	else if (!ft_strcmp(argv[i], "-s") && argv[i + 1])
		vm->f_show = ft_atoi(argv[++i]);
	else if (!ft_strcmp(argv[i], "-v"))
		vm->f_vus = 1;
	else if (!ft_strcmp(argv[i], "-log") && argv[i + 1])
		vm->f_log = ft_atoi(argv[++i]);
	else if (!ft_strcmp(argv[i], "-n") && argv[i + 1])
	{
		vm->players[vm->player_c].id = ft_atoi(argv[++i]);
		vm->players[vm->player_c].id_set = 1;
		if (argv[i + 1] && ft_check_ext(argv[i + 1]))
			vm->players[vm->player_c++].file_name = ft_strdup(argv[++i]);
		else
			ft_usage();
	}
	else if (argv[i] && ft_check_ext(argv[i]))
		vm->players[vm->player_c++].file_name = ft_strdup(argv[i]);
	else
		ft_usage();
	return (i);
}

t_vm			*ft_parse_args(int argc, char **argv)
{
	int		i;
	t_vm	*vm;

	i = 0;
	vm = ft_init_vm();
	while (i < argc)
		i = ft_check_flag(vm, i, argv) + 1;
	if (vm->player_c > MAX_PLAYERS)
		ft_usage();
	ft_check_ids(vm);
	return (vm);
}
