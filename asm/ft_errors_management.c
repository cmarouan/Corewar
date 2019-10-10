#include "asm.h"

const char *messages[4] = 
{
    "     Usage: ./asm <sourcefile1.s> <sourcefile2.s> ...",
    "We can't read files",
    "Syntax Error at line",
    "label not exist: "
};

void ft_errors_management(t_asm *store, char *str, int index)
{
    printf("%s: \"%s\"\n", messages[index], str);
    free_data(store);
    exit(1);
}
