#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include "op.h"
# include "ft_printf.h"

#include <ncurses.h>

# define SHIFT_ARG1 6
# define SHIFT_ARG2 4
# define SHIFT_ARG3 2

# define LIVES_LOG 1
# define CYCLES_LOG 2
# define INSTRUCTION_LOG 4
# define DEATHS_LOG 8
# define PC_MOV  16
# define SECOND 1000000

# define PC_INCR(vm, p, value) ft_change_pc(vm, p, value) 


typedef unsigned char	uint8_t;



typedef struct s_memory
{
	uint8_t	byte;
	int		p_id;
}				t_memory;


typedef struct		s_player
{
	int					id_set;
	int					id;
	char				*file_name;
	int					live_in_current_period;
	int 				last_live;
	char				prog_name[PROG_NAME_LENGTH + 1];
	int					prog_size;
	char				comment[COMMENT_LENGTH + 1];
	uint8_t				*code;
}					t_player;

typedef struct s_process
{
	// r1 start with champion number;
	char		opcode;
	int			*reg;
	int			oldindex;
	t_memory	*pc;
	int			carry;
	t_player	*player;
	int			cycle_to_wait;
	struct s_process *next;
}	t_process;


typedef struct s_op
{
	char	*name;
	int		argc;
	int		args[3];
	char	opcode;
	int		cycle;
	char	*comment;
	int		argtype;
	int		dir_size;
	int		carry;
}			t_op; 

typedef struct s_vm
{
	int			f_dump;
	int			f_show;
	int			f_vus;
	int			f_log;
	int			pause;
	int			last_live_player;
	int			nbr_live;
	int			current_cycle;
	int			cycle_from_start;
	int			nbr_of_check;
	int			cycle_to_die;
	int			player_c;
	int			speed;
	int			ids[MAX_PLAYERS + 1];
	t_player	players[MAX_PLAYERS];
	t_memory	*memory;
	void		(*instruction[16])(struct s_vm *, t_process *);
	int			pc_count;


	WINDOW		*w_memory;
	WINDOW		*w_info;

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
t_process *ft_add_pc(t_vm *vm, t_memory *mem, t_player *player);
void	ft_getbytes(t_memory *mem, t_memory *pc, int size, uint8_t *data);
void ft_free_vm(t_vm *vm);

void print_mem(t_memory *memory, t_memory *mem);
//instruction

void ft_exec(t_process *p, t_vm *vm);
void ft_check(t_vm *vm);
void ft_start(t_vm *vm);

void	ft_live(t_vm *vm, t_process *p);
void 	ft_ld(t_vm *vm, t_process *p);
void	ft_sti(t_vm *vm, t_process *p);
void	ft_add(t_vm *vm, t_process *p);
void	ft_sub(t_vm *vm, t_process *p);
void	ft_st(t_vm *vm, t_process *p);
void	ft_zjmp(t_vm *vm, t_process *p);
void	ft_and(t_vm *vm, t_process *p);


void ft_change_pc(t_vm *vm, t_process *p, int value);

void ft_print_pc_inc(int op, t_memory *tmp, int step);
void ft_write_mem(t_vm *vm, const char *data, int size,
                    t_memory *mem, t_player *p);

void ft_init_memory(t_vm *vm);
int     ft_valide(t_memory *mem, int index);




//vus
void vs_main(t_vm *vm);
int ft_int_vis(WINDOW **w_memory, WINDOW **w_info);
void ft_change_memory(int index, t_memory *mem, WINDOW *w_memory);
void left_window(WINDOW *w_memory, t_memory *mem);
void window_right(WINDOW *w_info, t_vm *vm);
//void ft_put_players(t_player *players, int nb_p, WINDOW *info);
void ft_move_pc(t_process *p, t_vm *vm);
int	ft_event_handler(t_vm *vm, int cmd);










#endif
