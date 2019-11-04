/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_player_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:03:10 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/04 15:00:27 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_check_code_size(int fd, int index, t_vm *vm)
{
	t_uint8 data[4];

	read(fd, data, 4);
	vm->players[index].prog_size = big_endian_to_int(data, 4);
	if (vm->players[index].prog_size > CHAMP_MAX_SIZE)
		ft_outerr(INVALID_CODE_SIZE, vm);
}

static void	ft_read_player_name(int fd, int index, t_vm *vm)
{
	int		j;
	t_uint8	data;

	j = 0;
	while (j < PROG_NAME_LENGTH)
	{
		read(fd, &data, 1);
		vm->players[index].prog_name[j] = data;
		j++;
	}
}

static void	ft_read_player_cmt(int fd, int index, t_vm *vm)
{
	int		j;
	t_uint8	data;

	j = 0;
	while (j < COMMENT_LENGTH)
	{
		read(fd, &data, 1);
		vm->players[index].comment[j] = data;
		j++;
	}
}

static void	ft_read_player_code(int fd, int index, t_vm *vm)
{
	vm->players[index].code =
				(t_uint8 *)ft_memalloc(vm->players[index].prog_size);
	if (!(vm->players[index].code))
		ft_outerr(errno, vm);
	read(fd, vm->players[index].code, vm->players[index].prog_size);
}

void		ft_parse_player_files(t_vm *vm)
{
	int	i;
	int	fd;

	i = 0;
	while (i < vm->player_c)
	{
		if ((fd = open(vm->players[i].file_name, O_RDONLY)) < 0)
			ft_outerr(errno, vm);
		ft_check_magic(fd, vm);
		vm->players[i].live_in_current_period = 0;
		ft_read_player_name(fd, i, vm);
		ft_read_null(fd, vm);
		ft_check_code_size(fd, i, vm);
		ft_read_player_cmt(fd, i, vm);
		ft_read_null(fd, vm);
		ft_read_player_code(fd, i, vm);
		close(fd);
		i++;
	}
}
