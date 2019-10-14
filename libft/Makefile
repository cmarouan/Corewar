# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/10 12:01:41 by hmney             #+#    #+#              #
#    Updated: 2019/10/11 15:39:12 by hmney            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	dequeue.c empty_queue.c enqueue.c free_queue.c free_tab.c ft_atoi.c ft_atol.c ft_bzero.c ft_ceil.c ft_delete_content.c ft_delete_node.c ft_hash_string.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isblank.c \
		ft_isdigit.c ft_isgraph.c ft_islower.c ft_isnumber.c ft_isprint.c ft_ispunct.c ft_isspace.c ft_isupper.c ft_itoa.c ft_length_number.c ft_lstadd.c ft_lstaddback.c ft_lstclear.c ft_lstdel.c ft_lstdelone.c \
		ft_lstfind.c ft_lstiter.c ft_lstlength.c ft_lstmap.c ft_lstnew.c ft_lstrev.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c \
		ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_search_characters.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c \
		ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c \
		ft_strsub.c ft_strtrim.c ft_tablen.c ft_tolower.c ft_toupper.c get_next_line.c ft_putbits_fd.c ft_putbits.c

OBJS_DIR = objs

INCLUDES = ../includes/

INCLUDES_FILES = $(addprefix $(INCLUDES),libft.h get_next_line.h)

OBJS =  $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

FLAGS = -Wextra -Werror -Wall

all: $(NAME)

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
