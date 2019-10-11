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

typedef unsigned char	uint8_t;

typedef struct		s_player
{
	int					id_set;
	int					id;
	char				*file_name;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
	uint8_t				*code;
}					t_player;

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
}			t_op;

typedef struct s_vm
{
	int			f_dump;
	int			f_show;
	int			f_vus;
	int			f_log;
	int			player_c;
	int			ids[MAX_PLAYERS + 1];
	t_player players[MAX_PLAYERS];


} t_vm;


typedef struct s_process
{
		int		reg_size;
		int		reg_num;
		// r1 start with champion number;
		void	*reg;
		void	*pc;
		int		carry;

}	t_process;

t_vm        *ft_parse_args(int argc, char **argv);
t_vm	*ft_init_vm();
void ft_usage(void);





#endif
