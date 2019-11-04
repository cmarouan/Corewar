/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:56:14 by kmoussai          #+#    #+#             */
/*   Updated: 2019/11/04 15:54:59 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include "op.h"
# include "ft_vdprintf.h"
# include <errno.h>
# include <ncurses.h>

# define SHIFT_ARG1 6
# define SHIFT_ARG2 4
# define SHIFT_ARG3 2
# define LIVES_LOG 1
# define CYCLES_LOG 2
# define INSTRUCTION_LOG 4
# define DEATHS_LOG 8
# define SECOND 1000000
# define INVALID_CODE_SIZE 0
# define INVALID_MAGIC_CODE 1
# define INVALID_NULL_BYTE 2
# define NULL_POINTER 3

# define MOD(index) index % MEM_SIZE
# define PC_INCR(vm, p, value) ft_change_pc(vm, p, value)

typedef unsigned char	t_uint8;

typedef struct			s_memory
{
	int					p_id;
	uint8_t				byte;
}						t_memory;

typedef struct			s_player
{
	int					id_set;
	int					id;
	int					live_in_current_period;
	int					last_live;
	int					prog_size;
	char				*file_name;
	uint8_t				*code;
	char				comment[COMMENT_LENGTH + 1];
	char				prog_name[PROG_NAME_LENGTH + 1];
}						t_player;

typedef struct			s_process
{
	int					pc_id;
	int					*reg;
	int					oldindex;
	int					carry;
	int					cycle_to_wait;
	int					live_declare;
	t_player			*player;
	t_memory			*pc;
	char				opcode;
	struct s_process	*next;
}						t_process;

typedef struct			s_operations
{
	int					argc;
	int					args[3];
	int					cycle;
	int					argtype;
	int					dir_size;
	int					carry;
	char				*name;
	char				opcode;
	char				*comment;
}						t_operations;

typedef struct			s_vm
{
	int					winner;
	int					pc_count;
	int					win;
	int					aff;
	int					aff_value;
	int					f_dump;
	int					f_show;
	int					f_vus;
	int					f_log;
	int					pc_ids;
	int					pause;
	int					nbr_live;
	int					current_cycle;
	int					cycle_from_start;
	int					nbr_of_check;
	int					cycle_to_die;
	int					player_c;
	int					speed;
	int					*ids;
	WINDOW				*w_memory;
	WINDOW				*w_info;
	t_player			*players;
	t_memory			*memory;
	void				(*instruction[16])(struct s_vm *, t_process *);
	t_process			*process;
}						t_vm;
t_operations			g_op_tab[17];
void					ft_parse_args(int argc, char **argv, t_vm *vm);
t_vm					*ft_init_vm(void);
void					ft_usage(void);
void					ft_outerr(int error, t_vm *vm);
int						big_endian_to_int(uint8_t *data, int size);
void					ft_parse_player_files(t_vm *vm);
void					ft_check_magic(int fd, t_vm *vm);
void					ft_read_null(int fd, t_vm *vm);
t_process				*ft_add_pc(t_vm *vm, int index, t_player *player);
void					ft_dup_process(t_vm *vm, t_process *p, int index);
t_process				*ft_kill_process(t_vm *vm, t_process *head,
										t_process *tmp, t_process *prev);
void					ft_getbytes(t_memory *mem, t_memory *pc, int size,
										uint8_t *data);
void					ft_free_vm(t_vm *vm);
void					print_mem(t_memory *memory);
void					ft_exec(t_process *p, t_vm *vm);
void					ft_check(t_vm *vm);
int						ft_start(t_vm *vm);
void					ft_live(t_vm *vm, t_process *p);
void					ft_ld(t_vm *vm, t_process *p);
void					ft_sti(t_vm *vm, t_process *p);
void					ft_add(t_vm *vm, t_process *p);
void					ft_sub(t_vm *vm, t_process *p);
void					ft_st(t_vm *vm, t_process *p);
void					ft_zjmp(t_vm *vm, t_process *p);
void					ft_ldi(t_vm *vm, t_process *p);
void					ft_and(t_vm *vm, t_process *p);
void					ft_or(t_vm *vm, t_process *p);
void					ft_xor(t_vm *vm, t_process *p);
void					ft_fork(t_vm *vm, t_process *p);
void					ft_lfork(t_vm *vm, t_process *p);
void					ft_lld(t_vm *vm, t_process *p);
void					ft_lldi(t_vm *vm, t_process *p);
void					ft_aff(t_vm *vm, t_process *p);
void					ft_change_pc(t_vm *vm, t_process *p, int value);
void					ft_write_mem(t_vm *vm, const char *data,
										t_memory *mem, t_player *p);
void					ft_init_memory(t_vm *vm);
int						ft_valide(uint8_t opcode, t_memory *mem, int index);
void					vs_main(t_vm *vm);
int						ft_int_vis(WINDOW **w_memory, WINDOW **w_info);
void					ft_change_memory(int index, t_memory *mem,
										WINDOW *w_memory);
void					left_window(WINDOW *w_memory, t_memory *mem);
void					window_right(WINDOW *w_info, t_vm *vm);
void					write_help(WINDOW *w_info);
void					ft_move_pc(t_process *p, t_vm *vm);
int						ft_event_handler(t_vm *vm, int cmd);

#endif
