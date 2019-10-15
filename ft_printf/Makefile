# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmney <hmney@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 18:38:02 by hmney             #+#    #+#              #
#    Updated: 2019/10/15 18:38:27 by hmney            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SOURCES_PRINTF = 	calcul_final_data.c calcul_float.c conversion_binary.c conversion_character.c conversion_decimal.c conversion_float.c  conversion_hexadecimal.c conversion_invalid.c conversion_octal.c \
					conversion_percent.c conversion_pointer.c conversion_string.c conversion_unsigned.c convert_binary.c ft_addition.c ft_exponent.c ft_itoa_base_uintmaxt.c ft_multiple.c ft_printf.c helping_functions.c \
					helping_functions2.c management_format.c mangement_displays.c

OBJS_DIR = objs

INCLUDES = ../includes/

INCLUDES_FILES = $(addprefix $(INCLUDES),libft.h get_next_line.h ft_printf.h)

OBJS =  $(addprefix $(OBJS_DIR)/,$(SOURCES_PRINTF:.c=.o))

FLAGS = -Wextra -Werror -Wall

all: _libft $(NAME)

_libft:
	@make -C ../libft

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJS): $(OBJS_DIR)/%.o : %.c $(INCLUDES_FILES) | $(OBJS_DIR)
	@gcc -o $@ -c $< $(FLAGS) -I $(INCLUDES)

clean:
	@/bin/rm -rf $(OBJS_DIR)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
