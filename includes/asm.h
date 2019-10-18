#ifndef ASM_H
# define ASM_H

# include "op.h"
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# define DBG(x) (ft_putendl(x));

typedef struct  s_args
{
	char        *arg;
	int         type_arg;
	int			code_arg;
	int			bytes_arg;
	int         label_index;
}               t_args;

typedef struct  s_label
{
	char		*name;
	int			index;
}               t_label;


typedef struct  s_token
{
	int         number_byte;
	char        *line;
	t_label		*label;
	char        *instruction;
	int			nb_arg;
	t_args      *args;
}               t_token;

typedef struct  s_file
{
	char        *name;
	char        *content;
	t_token     *code;
	t_list      *labels_definition;
	t_list      *labels_call;
	t_header    header;
}               t_file;

typedef struct	s_byte
{
	int 		number;
	int 		nb_byte;
}				t_byte;


void		read_files(t_list **files, int argc, char **argv);
void        ft_errors_management(t_list *files, t_file *file, char *str, int index);
t_token     *split_data(char const *s, char c);
int         header_checker(t_file *file, int *index);
int         check_label(char *label);
int         get_label(t_file *file, t_token *token, char *str, int *index);
void        labels_exist(t_list *files, t_file *file);
int         check_instruction(char *instruction);
int         get_instruction(t_token *token, char *str, int *index);
int         get_args(t_file *file, t_token *token, char *str, int *index);
int         statement_checker(t_file *file, int *index);
int         lexer(t_list *files, t_file *file);
void        free_data(t_list *files);
int 		convert_bytecode(t_file *file);
int			champion_exec_code(t_file *file, int fd);
char		*check_comment(char *str);
int			check_name_file(char *str, int set);
int			create_file(char *file_name, int set);
#endif