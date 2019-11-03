NAME = corewar
SRC =	srcs/op.c srcs/main.c\
		srcs/ft_parse_args.c\
		srcs/ft_process.c\
		srcs/ft_read_player_data.c\
		srcs/ft_tools.c\
		srcs/instruction/ft_live.c\
		srcs/instruction/ft_sti.c\
		srcs/instruction/ft_add.c\
		srcs/instruction/ft_sub.c\
		srcs/instruction/ft_zjmp.c\
		srcs/instruction/ft_ldi.c\
		srcs/instruction/ft_lldi.c\
		srcs/instruction/ft_ld.c\
		srcs/instruction/ft_lld.c\
		srcs/instruction/ft_st.c\
		srcs/instruction/ft_and.c\
		srcs/instruction/ft_or.c\
		srcs/instruction/ft_xor.c\
		srcs/instruction/ft_fork.c\
		srcs/instruction/ft_lfork.c\
		srcs/instruction/ft_aff.c\
		srcs/ft_visualisation.c\
		srcs/ft_memory_functions.c\
		srcs/ft_infos_functions.c\
		srcs/ft_check.c\
		srcs/ft_exec.c \
		srcs/ft_free_vm.c\
		srcs/ft_init.c\
		srcs/ft_start.c\
		srcs/ft_valide.c\
		
CFLAG = -Wall -Wextra -Werror -g
INC = includes


OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME): $(OBJ)
		make -C libft/
		make -C ft_printf/
		gcc -o $(NAME) $(OBJ) -L libft -lft -L ft_printf/ -lftprintf -lncurses

$(OBJ) : %.o : %.c
		gcc $(CFLAG) -o $@ -c $< -I $(INC) 

clean:
		make -C libft/ clean
		rm -rf $(OBJ)

fclean:clean
		make -C libft/ fclean
		rm -rf $(NAME) 

re: fclean $(NAME)
