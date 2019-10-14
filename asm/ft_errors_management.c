#include "asm.h"

const char *messages[7] = 
{
    "     Usage: ./asm <sourcefile1.s> <sourcefile2.s> ...",
    "We can't read the file",
    "the format of the file wrong",
    "Error at the header",
    "Syntax Error at line",
    "label doesn't exist : ",
    "We can't create the file *.cor"
};

void ft_errors_management(t_list *files, t_file *file, char *str, int index)
{
    if (file)
        printf("[%s] ", file->name);
    printf("%s", messages[index]);
    if (str)
        printf(" : \"%s\"",str);
    printf("\n");
    free_data(files);
    exit(1);
}
