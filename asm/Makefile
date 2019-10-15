# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmney <hmney@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 18:32:28 by hmney             #+#    #+#              #
#    Updated: 2019/10/15 19:05:26 by hmney            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

FLAG = -Wall -Wextra -Werror

SRCS = op.c champion_exec_code.c check_comment.c convert_bytecode.c free_data.c ft_errors_management.c get_args.c get_instructions.c get_label.c header_checker.c lexer.c main.c read_files.c split_data.c statement_checker.c 

LIBFT = ../libft/libft.a

LIBFT_PRINTF = ../ft_printf/libftprintf.a

OBJS_DIR = objs

INCLUDES = ../includes/

INCLUDES_FILES = $(addprefix $(INCLUDES),libft.h get_next_line.h ft_printf.h asm.h)

OBJ_ASM = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

all: _libft _printf $(NAME)

_libft:
	@make -C ../libft

_printf:
	@make -C ../ft_printf

$(NAME): $(LIBFT) $(OBJ_ASM)
	@gcc -g $(OBJ_ASM) $(LIBFT) $(LIBFT_PRINTF) -o $(NAME)


$(OBJ_ASM): $(OBJS_DIR)/%.o : %.c $(INCLUDES_FILES) | $(OBJS_DIR)
	@gcc -o $@ -c $< $(FLAG) -I $(INCLUDES)

clean:
	@make -C ../libft clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make -C ../libft fclean
	@rm -f $(NAME)
re: fclean all

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
