NAME = coreware
SRC = srcs/op.c srcs/main.c srcs/ft_parse_args.c
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
		make -C ft_printf/ clean
		rm -rf $(OBJ)

fclean:clean
		make -C libft/ fclean
		make -C ft_printf/ fclean
		rm -rf $(NAME) 

re: fclean $(NAME)
