#include "corewar.h"

void ft_free_vm(t_vm *vm)
{
	int i = 0;
	while (i < vm->pc_count)
	{
		free(vm->players[i].file_name);
		free(vm->players[i].code);
		i++;
	}
	
	free(vm->memory);
	free(vm);
}