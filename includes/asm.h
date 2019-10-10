#ifndef ASM_H
# define ASM_H

# include "op.h"
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include <stdio.h>
# define DBG(x) (ft_putendl(x));
typedef struct  s_token
{
    char        *label;
    char        *instruction;
    char        *args[3];
}               t_token;

typedef struct  s_file
{
    char        *name;
    char        *content;
    char        **code;
    t_list      *labels_definition;
    t_list      *labels_call;
    t_header    header;
    t_list      *tokens;
}               t_file;

typedef struct  s_asm
{
    t_list     *files;
}               t_asm;

int         read_files(t_asm *store, int argc, char **argv);
void        ft_errors_management(t_asm *store, char *str, int index);
char        **split_data(char const *s, char c);
int         header_checker(t_file *file, int *index);
int         check_label(char *label);
int         get_label(t_file *file, t_token *token, char *str, int *index);
void        labels_exist(t_asm *store, t_file *file);
int         check_instruction(char *instruction);
int         get_instruction(t_token *token, char *str, int *index);
int         get_args(t_file *file, t_token *token, char *str, int *index);
int         statement_checker(t_file *file, int *index);
int         validation_files(t_asm *store, int argc, char **argv);
int         lexer(t_asm *store, t_file *file);
void        free_data(t_asm *store);
#endif