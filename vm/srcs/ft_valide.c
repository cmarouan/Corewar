#include "corewar.h"


int     ft_argsize(uint8_t opcode, uint8_t arg)
{
    if (arg == 0b01)
        return (1);
    else if (arg == 0b10)
        return (op_tab[opcode - 1].dir_size);
    else
        return (2);
}
/*
pc need to be in opcode position before calling a valid function.
mem : adress memory of the first arg;
argtype : argtype of operation
opcode : operation code 
*/
int     ft_valide(uint8_t opcode,/* t_process *p, t_vm *vm*/ uint8_t argtype, t_memory *mem)
{
    int size;
    int i;
    int wrong;
    int arg;

    i = 0;
    size = 0;
    wrong = 0;
    //ft_printf("%b\n", argtype);
    while (i < op_tab[opcode - 1].argc)
    {
        arg = argtype >> (6 - i*2);
        arg = (arg == 0b11 ? 4 : arg); 
        if (arg == 0b01)
            if (mem[size%MEM_SIZE].byte <= 0 || mem[size%MEM_SIZE].byte > 16)
                wrong++;
        
        size += ft_argsize(opcode, (arg == 4 ? 0b11 : arg));
        //ft_printf("size at [%d, %.2b] : %d\n", i, (arg == 4 ? 0b11 : arg), size);
        if ((arg & op_tab[opcode - 1].args[i]) == 0)
            wrong++;
        arg = (arg == 4 ? 0b11 : arg);
        argtype = argtype ^ (arg << (6 - i*2));
        i++;
    }
    return (wrong ? size  + 2 : -1);
}

// // 1 + 2 + 1

// int main()
// {
//     t_memory m[6] = {
//                         {
//                             .byte = 6
//                         },
//                         {
//                             .byte = 0b01010100
//                         },
//                         {
//                             .byte = 0xF
//                         },
//                         {
//                             .byte = 0x05
//                         },
//                         {
//                             .byte = 0x07
//                         },
//                         {
//                             .byte = 0x00
//                         },
//                         {
//                             .byte = 0x01
//                         }
//                     };
//     ft_printf("%s\n", op_tab[m[0].byte - 1].name);
//     //return 0;
//     printf("%d\n", ft_valide(m[0].byte, m[1].byte, m + 2));
//     return 0;
// }