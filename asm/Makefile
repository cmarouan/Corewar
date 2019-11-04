# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmney <hmney@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 18:32:28 by hmney             #+#    #+#              #
#    Updated: 2019/11/04 22:52:17 by hmney            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

FLAG = -Wall -Wextra -Werror

SRCS = op.c champion_exec_code.c check_comment.c convert_bytecode.c free_data.c ft_errors_management.c get_args.c get_instructions.c get_label.c header_checker.c lexer.c main.c read_files.c split_data.c statement_checker.c disassembler.c helping_get_args.c helping_disassembler.c

LIBFT = ../libft/libft.a

VDPRINTF = ../ft_vdprintf/libftvdprintf.a

OBJS_DIR = objs

INCLUDES = ../includes/

INCLUDES_FILES = $(addprefix $(INCLUDES),libft.h get_next_line.h ft_vdprintf.h asm.h)

OBJ_ASM = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

all: _libft _vdprintf $(NAME)

_libft:
	@make -C ../libft

_vdprintf:
	@make -C ../ft_vdprintf

$(NAME): $(LIBFT) $(OBJ_ASM) $(VDPRINTF)
	@gcc -g $(OBJ_ASM) $(LIBFT) $(VDPRINTF) -o $(NAME) $(FLAG)


$(OBJ_ASM): $(OBJS_DIR)/%.o : %.c $(INCLUDES_FILES) | $(OBJS_DIR)
	@gcc -o $@ -c $< $(FLAG) -I $(INCLUDES)

clean:
	@make -C ../libft clean
	@make -C ../ft_vdprintf clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make -C ../libft fclean
	@make -C ../ft_vdprintf fclean
	@rm -f $(NAME)
re: fclean all

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
