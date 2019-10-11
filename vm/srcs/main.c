/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:37:45 by kmoussai          #+#    #+#             */
/*   Updated: 2019/10/11 19:10:32 by kmoussai         ###   ########.fr       */
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


int main(int argc, char **argv)
{
	t_vm *vm;

	if (argc == 1 && argv[0])
    {
        ft_usage();
        return (0);
    }
	vm = ft_parse_args(argc, argv);

	ft_printf("dump flag %d\n", vm->f_dump);
	ft_printf("log flag %d\n", vm->f_log);
	ft_printf("Show flag %d\n", vm->f_show);
	ft_printf("visualizer flag %d\n", vm->f_vus);
	int i = 0;
	while (i < vm->player_c)
	{
		ft_printf("player file <%s> id %d\n", vm->players[i].file_name, vm->players[i].id);
		i++;
	}
	
}

