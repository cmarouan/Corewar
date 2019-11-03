/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_player_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:03:10 by cmarouan          #+#    #+#             */
/*   Updated: 2019/11/03 17:04:22 by cmarouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_check_code_size(int fd, int index, t_vm *vm)
{
	uint8_t data[4];

	read(fd, data, 4);
	vm->players[index].prog_size = big_endian_to_int(data, 4);
	if (vm->players[index].prog_size > CHAMP_MAX_SIZE)
		ft_outerr(INVALID_CODE_SIZE, vm);
}

static void	ft_read_player_name(int fd, int index, t_vm *vm)
{
	int		j;
	uint8_t	data;

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
	uint8_t	data;

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
	vm->players[index].code = (uint8_t *)malloc(vm->players[index].prog_size);
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

void		ft_check_magic(int fd, t_vm *vm)
{
	uint8_t	data[4];

	read(fd, data, 4);
	if (big_endian_to_int(data, 4) != COREWAR_EXEC_MAGIC)
	{
		ft_outerr(INVALID_MAGIC_CODE, vm);
	}
}

void		ft_read_null(int fd, t_vm *vm)
{
	int		i;
	uint8_t	data[4];

	read(fd, &data, 4);
	i = 0;
	while (i < 4)
		if (data[i++] != 0x00)
			ft_outerr(INVALID_NULL_BYTE, vm);
}
