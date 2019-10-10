#include "asm.h"

int main(int argc, char **argv)
{
    t_asm *store;

    if (!(store = (t_asm *)ft_memalloc(sizeof(t_asm))))
        return (1);
    if (argc == 1)
        ft_errors_management(store, NULL, 0);
    if (!(validation_files(store, argc, argv)))
        return (1);
    free_data(store);
    return (0);
}