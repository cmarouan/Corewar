#include "corewar.h"



static void	ft_check_code_size(int fd, int index, t_vm *vm)
{
	uint8_t *data;


	data = (uint8_t *)malloc(4);
	read(fd, data, 4); // read code size;
	vm->players[index].prog_size = big_endian_to_int(data, 4);
	if (vm->players[index].prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf("Error in CHAMP_MAX_SIZE for player %s\n",
                vm->players[index].file_name);
		free(data);
		ft_outerr(vm->players[index].file_name);
	}
	free(data);
}

static void	ft_read_player_name(int fd, int index, t_vm *vm)
{
	int j;
	uint8_t data;

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
	int j;
	uint8_t data;

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
	//char data;
	//int		i;
	
	vm->players[index].code = (uint8_t *)malloc(vm->players[index].prog_size);
	read(fd, vm->players[index].code, vm->players[index].prog_size);
	// i = 0;
	// while (i < (int)vm->players[index].prog_size)
	// {
	// 	read(fd, &data, 1);
	// 	vm->players[index].code[i] = data;
	// 	i++;
	// }
}

void	ft_parse_player_files(t_vm *vm)
{
	int i;
	int fd;

	i = 0;
	while (i < vm->player_c)
	{
		if ((fd = open(vm->players[i].file_name, O_RDONLY)) <= 0)
			//ft_outerr("file not open");
			ft_outerr(vm->players[i].file_name);
		ft_check_magic(fd, vm->players[i].file_name);
		vm->players[i].live_in_current_period = 0;
		ft_read_player_name(fd, i, vm);
		ft_printf("%s has name %s\n", vm->players[i].file_name, vm->players[i].prog_name);
		ft_read_null(fd);
		ft_check_code_size(fd, i, vm);
		ft_printf("%s has code size %d\n", vm->players[i].file_name, vm->players[i].prog_size);
		ft_read_player_cmt(fd, i, vm);
	//	ft_printf("%s has cmt %s\n", vm->players[i].file_name, vm->players[i].comment);
		ft_read_null(fd);
		ft_read_player_code(fd, i, vm);
		int j = 0;
		printf("code :\n");
		while (j < (int)vm->players[i].prog_size)
		{
			printf("%#.2X ", vm->players[i].code[j]);
			j++;
		}
		printf("\n");
		//exit(0);

		close(fd);
		i++;
	}
}

void	ft_check_magic(int fd, char *filename)
{
	uint8_t 	*data;

	data = (uint8_t *)malloc(4);
	read(fd, data, 4); // read magic number;
	if (big_endian_to_int(data, 4) != COREWAR_EXEC_MAGIC)
	{
		ft_printf("Error in COREWAR_EXEC_MAGIC for player %s %x\n", filename, big_endian_to_int(data, 4));
		free(data);
		ft_outerr(filename);
	}
	free(data);
}

void	ft_read_null(int fd)
{
	int		i;
	uint8_t data[4];

	read(fd, &data, 4);
	i = 0;
	while (i < 4)
		if (data[i++] != 0x00)
			ft_outerr("Byte  Code Err");
}