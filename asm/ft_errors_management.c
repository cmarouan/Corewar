/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:04:42 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 18:55:24 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

const char	*g_messages_asm[7] = {
	"     Usage: ./asm [-d] <sourcefile1.s> <sourcefile2.s> ...",
	"We can't read the file",
	"the format of the file is wrong",
	"Error at the header",
	"Syntax Error at line",
	"label doesn't exist",
	"We can't create the file *.cor"
};

const char	*g_messages_dasm[4] = {
	"the format of the file is wrong:",
	"We can't read the file:",
	"Something wrong in the bytecode in the file:",
	"     Usage: ./asm [-d] <sourcefile1.s> <sourcefile2.s> ..."
};

void	ft_errors_management(t_list *files, t_file *file, char *str, int index)
{
	if (file)
		ft_printf("[%s] ", file->name);
	ft_printf("%s", g_messages_asm[index]);
	if (str)
		ft_printf(" : \"%s\"", str);
	else
		ft_printf(" : \"(NULL)\"");
	ft_printf("\n");
	free_data(files);
	exit(1);
}

void	ft_errors_management2(char *str, int index)
{
	ft_printf("%s", g_messages_dasm[index]);
	if (str)
		ft_printf(" %s", str);
	ft_printf("\n");
	exit(1);
}
