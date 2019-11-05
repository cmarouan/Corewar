# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmney <hmney@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/03 22:30:07 by hmney             #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2019/11/05 10:47:50 by hmney            ###   ########.fr        #
=======
#    Updated: 2019/11/05 10:47:05 by kmoussai         ###   ########.fr        #
>>>>>>> a4b0acaf89109d0612a020b08069802bd2912418
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
