#include "asm.h"
# define NAME_CMD_STRING ".name"

int main(int argc, char **argv)
{
    int fd;
    char *prog_name = " tetst.s";
    fd = open("str", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    ft_printf("houssame %s \"%s\"\n", NAME_CMD_STRING, prog_name);
    return (0);
}