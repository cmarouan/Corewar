/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:37:45 by kmoussai          #+#    #+#             */
/*   Updated: 2019/10/13 12:07:09 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op op_tab[17];

void ft_usage(void)
{
    ft_printf("usage : ./corewar [(-dump | -d) <N>] [-log] [-s <N>]");
	ft_printf(" [-v] [-n <N> <champion.cor>]");
	ft_printf(" [<champion.cor> <champion.cor> <...>]\n");
	ft_printf("-(d/dump) <N> : Dumps memory after N cycles then exits\n");
	ft_printf("%-9s <N> : Set <N> of the next player\n", "-n");
	ft_printf("%-9s <N> : Runs N cycles, dumps memory, pauses", "-s");
	ft_printf(",then repeats\n%-9s <N> : Logs levels\n", "-log");
	ft_printf("%20d : %s", 1, "Show Lives\n");
	ft_printf("%20d : %s", 2, "Show Cycles\n");
	ft_printf("%20d : %s", 4, "Show Operations\n");
	ft_printf("%20d : %s", 8, "Show Deaths\n");
	ft_printf("%20d : %s", 16, "Show PC movements\n");
	ft_printf("%-13s : Run visualizer\n", "-v");
	exit(0);
}

int big_endian_to_int(uint8_t *data, int size)
{
	int neg;
	int result;
	int i;

	i = -1;
	result = 0;
	neg = data[0] & 0x80;
	while (++i < size)
		result |= ((0 + data[i]) << (size - 1 - i) * 8);
	if (neg && size == 2)
		return (result - 0xFFFF - 1);
	return (result);
}    


int ft_check_argtype(uint8_t *argtype, int shift, int opcode)
{
	int j = 0;

	if (*argtype >> shift == REG_CODE)
	{
		ft_printf("REG_CODE ");
		*argtype ^= (1 << shift);
		j += 1;
	}
	else if (*argtype >> shift == DIR_CODE)
	{
		ft_printf("DIR_CODE ");
		*argtype ^= (2 << shift);
		//j 
		j += (op_tab[(int)opcode - 1].dir_size_2) ? 2: 4;
	}
	else if (*argtype >> shift == IND_CODE)
	{
		*argtype ^= (3 << shift);
		ft_printf("IND_CODE ");
		j += 2;
	}
	return j;
}


t_vm	*ft_init_vm()
{
	t_vm *vm;
	
	vm = (t_vm *)malloc(sizeof(t_vm));
	vm->f_dump = -1;
	vm->f_show = -1;
	vm->f_vus = 0;
	vm->f_log = 0;
	vm->player_c = 0;
	return (vm);
}

void	ft_outerr(char *msg)
{
	ft_printf("ERROR : %s\n", msg);
	exit(0);
}

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void print_mem(t_memory *memory)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		//if (memory[i%MEM_SIZE].isplayer)
	 		//ft_printf(KRED "%.2X " KNRM, memory[i%MEM_SIZE].byte );
		//else
		if (memory[i%MEM_SIZE].color)
			ft_printf("%s", memory[i%MEM_SIZE].color);
		ft_printf("%.2X " KNRM,  memory[i%MEM_SIZE].byte );
		if ((i + 1)%64 == 0)
	 		printf("\n");
		i++;
	}
}

int main(int argc, char **argv)
{
	t_vm *vm;

	if (argc == 1 && argv[0])
    {
        ft_usage();
        return (0);
    }
	vm = ft_parse_args(argc, argv);

	// ft_printf("dump flag %d\n", vm->f_dump);
	// ft_printf("log flag %d\n", vm->f_log);
	// ft_printf("Show flag %d\n", vm->f_show);
	// ft_printf("visualizer flag %d\n", vm->f_vus);
	// int i = 0;
	// while (i < vm->player_c)
	// {
	// 	ft_printf("player file <%s> id %d\n", vm->players[i].file_name, vm->players[i].id);
	// 	i++;
	// }

	ft_parse_player_files(vm);

	vm->memory = (t_memory *)malloc(sizeof(t_memory) * MEM_SIZE);
	char *color[] = {KGRN, KRED, KBLU, KCYN};
	int i = -1;
	while (++i < MEM_SIZE)
	{
		vm->memory[i].byte = 0;
		vm->memory[i].color = NULL;
	}
	int j;
	i = 0;
	while (i < vm->player_c)
	{
		j = (MEM_SIZE/vm->player_c)*i;
		int h = 0;
		while (h < (int)vm->players[i].prog_size)
		{
			vm->memory[j%MEM_SIZE].byte = vm->players[i].code[h];
			vm->memory[j%MEM_SIZE].color = strdup(color[i]);
			h++;
			j++;
		}
		i++;
	}
	print_mem(vm->memory);
	// ii = MEM_SIZE/2;
	// 	 j = 0;
	//  while (j < (int)player_head[0].prog_size)
	//  {
	//  	memory[i%MEM_SIZE] = player_head[0].code[j];
	// 	i++;
	// 	j++;
	// }
	
/*
		j = 0;
		while (j < (int)player_head[i].prog_size)
		{
			//read(fd[i], data, 1);
			//player_head[i].code[j] = data[0];
			uint8_t opcode =  player_head[i].code[j];
			if (opcode >= 1 && opcode <= 16)
				ft_printf("%s ", op_tab[(int)opcode - 1].name);m
			else
				ft_printf("%#.2X ", opcode);
			
			//j++;
			uint8_t argtype = 0;
			if((opcode >= 1 && opcode <= 16 && op_tab[(int)opcode - 1].argc > 1) || opcode == 0x10)
				argtype = player_head[i].code[++j];
			else
			{
				//op_tab[(int)opcode - 1].args[0]
				ft_printf("T_DIR\n");
				j += (op_tab[(int)opcode - 1].dir_size_2) ? 2: 4;
				//ft_printf("%d\n", j + 1);
				//ft_printf("\n next byte to read %d ", j + 1);
				//break;
				j++;
				continue;
			}
			j++;
			
			//ft_printf("%.8b\n", argtype);
			//first arg type:
			j += ft_check_argtype(&argtype, SHIFT_ARG1, opcode);			
			//second arg type:
			j += ft_check_argtype(&argtype, SHIFT_ARG2, opcode);
			
			//ft_printf("\n next byte to read %d ", j + 1);
			//third arg type:
			j += ft_check_argtype(&argtype, SHIFT_ARG3, opcode);
			//ft_printf("\n next byte to read %d ", j + 1);
			//break;

			ft_printf("\n");
			
			//break;
		
			//j++;
		}
*/
/*
	 uint8_t *memory = (uint8_t *)malloc(MEM_SIZE);
	 ft_memset(memory, 0, MEM_SIZE);
	 	i = MEM_SIZE/2;
		 j = 0;
	 while (j < (int)player_head[0].prog_size)
	 {
	 	memory[i%MEM_SIZE] = player_head[0].code[j];
		i++;
		j++;
	}
	 	i = 0;
	 while (i < MEM_SIZE)
	 {
	 	printf("%.2X ", memory[i%MEM_SIZE]);
		if ((i + 1)%64 == 0)
	 		printf("\n");

		i++;
	}*/
	
	return (0);
}

