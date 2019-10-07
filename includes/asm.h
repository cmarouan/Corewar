#ifndef ASM_H
# define ASM_H

# include "op.h"
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

typedef struct  s_token
{
    char        *label;
    char        *instruction;
    char        *arg1;
    char        *arg2;
    char        *arg3;
}               t_token;

typedef struct  s_file
{
    char        *name;
    char        *content;
    char        **code;
    t_header    header;
    t_list      *tokens;
}               t_file;

typedef struct  s_asm
{
    t_list     *files;
}               t_asm;

int read_files(t_asm *store, int argc, char **argv);
void ft_errors_management(t_asm *store, int index, int line);
char		**split_data(char const *s, char c);
void free_data(t_asm *store);
#endif