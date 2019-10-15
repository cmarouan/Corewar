#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include "op.h"
# include "ft_printf.h"

# define SHIFT_ARG1 6
# define SHIFT_ARG2 4
# define SHIFT_ARG3 2

# define PC_INCR(vm, p, value) ft_change_pc(vm, p, value) 



#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

typedef unsigned char	uint8_t;



typedef struct s_memory
{
	uint8_t byte;
	char	*color;
	int		p_id;
}				t_memory;


typedef struct		s_player
{
	int					id_set;
	int					id;
	char				*color;
	char				*file_name;
	int					live_in_current_cycle;
	int 				last_live;
	char				prog_name[PROG_NAME_LENGTH + 1];
	int					prog_size;
	char				comment[COMMENT_LENGTH + 1];
	uint8_t				*code;
}					t_player;

typedef struct s_process
{
	// r1 start with champion number;
	int			*reg;
	t_memory	*pc;
	int			carry;
	t_player	*player;
	struct s_process *next;
}	t_process;


typedef struct s_op
{
	char	*name;
	int		argc;
	int		args[3];
	uint8_t opcode;
	int		cycle;
	char	*comment;
	int		octet_param;
	int		dir_size_2;
	int		carry;
}			t_op;



typedef struct s_vm
{
	int			f_dump;
	int			f_show;
	int			f_vus;
	int			f_log;
	int			last_live_player;
	int			nbr_live;
	int			current_cycle;
	int			player_c;
	int			ids[MAX_PLAYERS + 1];
	t_player	players[MAX_PLAYERS];
	t_memory	*memory;
	void		(*instruction[2])(struct s_vm *, t_process *);
	int			pc_count;
	t_process	*process;


} t_vm;


t_op op_tab[17];


t_vm    *ft_parse_args(int argc, char **argv);
t_vm	*ft_init_vm();
void 	ft_usage(void);

void	ft_outerr(char *msg);
int 	big_endian_to_int(uint8_t *data, int size);
void	ft_parse_player_files(t_vm *vm);
void	ft_check_magic(int fd, char *filename);
void	ft_read_null(int fd);
t_process *ft_add_pc(t_process *p, t_memory *mem, t_player *player);
void	ft_getbytes(t_memory *mem, t_memory *pc, int size, uint8_t data[]);

void print_mem(t_memory *memory, t_memory *mem);
//instruction

void	ft_live(t_vm *vm, t_process *p);
void	ft_sti(t_vm *vm, t_process *p);

void ft_change_pc(t_vm *vm, t_process *p, int value);






#endif
