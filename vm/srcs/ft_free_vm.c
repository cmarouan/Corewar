#include "corewar.h"

void ft_free_vm(t_vm *vm)
{
	t_process *tmp = vm->process;
	t_process *prev;

	int i = 0;
	while (i < vm->player_c)
	{
		//free(vm->players[i].file_name);
		free(vm->players[i].code);
		i++;
	}
	free(vm->players);
	free(vm->ids);
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		free(prev->reg);
		free(prev);
	}
	//free(vm->instruction[0]);
	free(vm->memory);
	free(vm);
}