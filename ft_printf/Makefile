NAME = libftprintf.a

SOURCES_PRINTF = Sources/calcul_float.c Sources/calcul_final_data.c Sources/conversion_character.c Sources/conversion_decimal.c Sources/conversion_float.c Sources/conversion_hexadecimal.c Sources/conversion_octal.c Sources/conversion_binary.c Sources/conversion_percent.c Sources/conversion_invalid.c Sources/conversion_pointer.c Sources/conversion_string.c Sources/conversion_unsigned.c Sources/convert_binary.c Sources/ft_addition.c Sources/ft_exponent.c Sources/ft_itoa_base_uintmaxt.c Sources/ft_multiple.c Sources/ft_printf.c Sources/helping_functions.c Sources/helping_functions2.c Sources/management_format.c Sources/mangement_displays.c
SOURCES_LIBFT = ../libft/dequeue.c ../libft/empty_queue.c ../libft/enqueue.c ../libft/free_queue.c ../libft/free_tab.c ../libft/ft_atoi.c ../libft/ft_atol.c ../libft/ft_bzero.c ../libft/ft_ceil.c ../libft/ft_delete_content.c ../libft/ft_delete_node.c ../libft/ft_hash_string.c ../libft/ft_isalnum.c ../libft/ft_isalpha.c ../libft/ft_isascii.c ../libft/ft_isblank.c ../libft/ft_isdigit.c ../libft/ft_isgraph.c ../libft/ft_islower.c ../libft/ft_isnumber.c ../libft/ft_isprint.c ../libft/ft_ispunct.c ../libft/ft_isspace.c ../libft/ft_isupper.c ../libft/ft_itoa.c ../libft/ft_length_number.c ../libft/ft_lstadd.c ../libft/ft_lstaddback.c ../libft/ft_lstclear.c ../libft/ft_lstdel.c ../libft/ft_lstdelone.c ../libft/ft_lstfind.c ../libft/ft_lstiter.c ../libft/ft_lstlength.c ../libft/ft_lstmap.c ../libft/ft_lstnew.c ../libft/ft_lstrev.c ../libft/ft_memalloc.c ../libft/ft_memccpy.c ../libft/ft_memchr.c ../libft/ft_memcmp.c ../libft/ft_memcpy.c ../libft/ft_memdel.c ../libft/ft_memmove.c ../libft/ft_memset.c ../libft/ft_putchar.c ../libft/ft_putchar_fd.c ../libft/ft_putendl.c ../libft/ft_putendl_fd.c ../libft/ft_putnbr.c ../libft/ft_putnbr_fd.c ../libft/ft_putstr.c ../libft/ft_putstr_fd.c ../libft/ft_search_characters.c ../libft/ft_strcat.c ../libft/ft_strchr.c ../libft/ft_strclr.c ../libft/ft_strcmp.c ../libft/ft_strcpy.c ../libft/ft_strdel.c ../libft/ft_strdup.c ../libft/ft_strequ.c ../libft/ft_striter.c ../libft/ft_striteri.c ../libft/ft_strjoin.c ../libft/ft_strlcat.c ../libft/ft_strlen.c ../libft/ft_strmap.c ../libft/ft_strmapi.c ../libft/ft_strncat.c ../libft/ft_strncmp.c ../libft/ft_strncpy.c ../libft/ft_strnequ.c ../libft/ft_strnew.c ../libft/ft_strnstr.c ../libft/ft_strrchr.c ../libft/ft_strsplit.c ../libft/ft_strstr.c ../libft/ft_strsub.c ../libft/ft_strtrim.c ../libft/ft_tablen.c ../libft/ft_tolower.c ../libft/ft_toupper.c ../libft/get_next_line.c

SOURCES_O = calcul_final_data.o calcul_float.o conversion_binary.o conversion_character.o conversion_decimal.o conversion_float.o conversion_hexadecimal.o conversion_invalid.o conversion_octal.o conversion_percent.o conversion_pointer.o conversion_string.o conversion_unsigned.o convert_binary.o dequeue.o empty_queue.o enqueue.o free_queue.o free_tab.o ft_addition.o ft_atoi.o ft_atol.o ft_bzero.o ft_ceil.o ft_delete_content.o ft_delete_node.o ft_exponent.o ft_hash_string.o ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isblank.o ft_isdigit.o ft_isgraph.o ft_islower.o ft_isnumber.o ft_isprint.o ft_ispunct.o ft_isspace.o ft_isupper.o ft_itoa.o ft_itoa_base_uintmaxt.o ft_length_number.o ft_lstadd.o ft_lstaddback.o ft_lstclear.o ft_lstdel.o ft_lstdelone.o ft_lstfind.o ft_lstiter.o ft_lstlength.o ft_lstmap.o ft_lstnew.o ft_lstrev.o ft_memalloc.o ft_memccpy.o ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memdel.o ft_memmove.o ft_memset.o ft_multiple.o ft_printf.o ft_putchar.o ft_putchar_fd.o ft_putendl.o ft_putendl_fd.o ft_putnbr.o ft_putnbr_fd.o ft_putstr.o ft_putstr_fd.o ft_search_characters.o ft_strcat.o ft_strchr.o ft_strclr.o ft_strcmp.o ft_strcpy.o ft_strdel.o ft_strdup.o ft_strequ.o ft_striter.o ft_striteri.o ft_strjoin.o ft_strlcat.o ft_strlen.o ft_strmap.o ft_strmapi.o ft_strncat.o ft_strncmp.o ft_strncpy.o ft_strnequ.o ft_strnew.o ft_strnstr.o ft_strrchr.o ft_strsplit.o ft_strstr.o ft_strsub.o ft_strtrim.o ft_tablen.o ft_tolower.o ft_toupper.o get_next_line.o helping_functions.o helping_functions2.o management_format.o mangement_displays.o

FLAGS = -Wall -Wextra -Werror
INCLUDE_PATH = ../includes/

all: $(NAME)

$(NAME) :
	@gcc $(FLAGS) -c $(SOURCES_PRINTF) $(SOURCES_LIBFT) -I $(INCLUDE_PATH)
	@ar rc $(NAME) $(SOURCES_O)
	@ranlib $(NAME)

clean :
	@/bin/rm -f $(SOURCES_O)

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all
