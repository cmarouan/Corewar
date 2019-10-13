NAME = corewar
SRC = srcs/op.c srcs/main.c srcs/ft_parse_args.c srcs/ft_read_player_data.c
		
CFLAG = -Wall -Wextra -Werror
INC = includes


OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME): $(OBJ)
		make -C libft/
		make -C ft_printf/
		gcc -o $(NAME) $(OBJ) -L libft -lft -L ft_printf/ -lftprintf

$(OBJ) : %.o : %.c
		gcc $(CFLAG) -o $@ -c $< -I $(INC) 

clean:
		make -C libft/ clean
		rm -rf $(OBJ)

fclean:clean
		make -C libft/ fclean
		rm -rf $(NAME) 

re: fclean $(NAME)
