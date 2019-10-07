#include "asm.h"

const char *messages[3] = 
{
    "     Usage: ./asm <sourcefile1.s> <sourcefile2.s> ...",
    "We can't read files",
    "Syntax Error at ligne "
};

void ft_errors_management(t_asm *store, int index, int line)
{
    ft_putstr(messages[index]);
    if (line)
    {
        ft_putnbr(line);
        ft_putchar('\n');
    }
    else
        ft_putchar('\n');
    free_data(store);
    exit(1);
}
