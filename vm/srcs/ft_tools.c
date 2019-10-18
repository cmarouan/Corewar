#include "corewar.h"

void ft_write_mem(t_vm *vm, const char *data, int size,
                    t_memory *mem, t_player *p)
{
    int i;

    i = size - 1;
    while (i >= 0)
    {
        if ((mem - vm->memory) >= MEM_SIZE)
			mem = mem - MEM_SIZE;
        mem->byte = data[i];
        mem->p_id = p->id;
        ft_change_memory(mem - vm->memory, mem, vm->w_memory);
        mem++;
        i--;
    }
}

void ft_change_pc(t_vm *vm, t_process *p, int value)
{
    int diff;
   // if (!vm->f_vus)
     //   ft_printf("pc %p , memory %p\n", p->pc, vm->memory);
    p->oldindex = p->pc - vm->memory;
    diff = (p->pc - vm->memory) + value;
    if (diff >= 0 && diff < MEM_SIZE)
        p->pc += value;
    else if (diff >= MEM_SIZE)
        p->pc = vm->memory + diff - MEM_SIZE;
    else if (diff < 0)
        p->pc = vm->memory + MEM_SIZE + diff;
    if (vm->f_vus)
		ft_move_pc(p, vm);
}


void ft_print_pc_inc(int op, t_memory *tmp, int step)
{
	ft_printf("INC_PC %d (%X > %X) : %.2X",step + 1, tmp, tmp + step, op);
	while (step--)
	{
		ft_printf(" %02X", tmp->byte);
		tmp++;
	}
	ft_printf("\n");
}


void ft_getbytes(t_memory *mem, t_memory *pc, int size, uint8_t *data)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if ((pc - mem) >= MEM_SIZE)
			pc = pc - MEM_SIZE;
		data[i] = pc->byte;
		pc++;
		i++;
	}
}


int big_endian_to_int(uint8_t *data, int size)
{
	int neg;
	int result;
	int i;
	//uint8_t *data;

	i = -1;
	result = 0;
	if (!data)
		ft_outerr("Null pointer");
	neg = *data & 0x80;
	while (++i < size)
		result |= ((0 + data[i]) << (size - 1 - i) * 8);
	if (neg && size == 2)
		return (result - 0xFFFF - 1);
	return (result);
}


void print_mem(t_memory *memory, t_memory *pc)
{
	int i;

	//system("clear");
	
	char *color[] = {KGRN, KRED, KBLU, KCYN};
	i = 0;
	while (i < MEM_SIZE)
	{
		//if (memory[i%MEM_SIZE].isplayer)
	 		//ft_printf(KRED "%.2X " KNRM, memory[i%MEM_SIZE].byte );
		//else
		
		if (memory + i%MEM_SIZE == pc)
			ft_printf("%s", KRED);
		else if (memory[i%MEM_SIZE].p_id != -1)
			ft_printf("%s", color[memory[i%MEM_SIZE].p_id - 1]);
		
		ft_printf("%.2X " KNRM,  memory[i%MEM_SIZE].byte );
		if ((i + 1)%64 == 0)
	 		printf("\n");
		i++;
	}
}