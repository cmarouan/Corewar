#include "asm.h"

int main(int argc, char **argv)
{
    int x = 0b11101100;
    int i = -1;
    int tab[3];
    int shift = 6;

    for(int i=0;i<3;i++)
        tab[i] = 0;
    while (++i < 3)
    {
        tab[i] = x >> shift;
        x ^= tab[i] << shift;
        shift -= 2;
    }
    for(int i=0;i<3;i++)
        printf("%d\n", tab[i]);
    return (0);
}