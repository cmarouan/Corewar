# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/03 22:30:07 by hmney             #+#    #+#              #
#    Updated: 2019/11/05 11:54:05 by kmoussai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C libft
	@make -C ft_vdprintf
	@make -C asm
	@make -C vm

clean:
	@make clean -C libft
	@make clean -C ft_vdprintf
	@make clean -C asm
	@make clean -C vm

fclean:
	@make fclean -C libft
	@make fclean -C ft_vdprintf
	@make fclean -C asm
	@make fclean -C vm
re: fclean all
