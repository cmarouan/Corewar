/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:04:42 by hmney             #+#    #+#             */
/*   Updated: 2019/10/15 23:25:27 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

const char	*g_messages[7] = {
	"     Usage: ./asm [-d] <sourcefile1.s> <sourcefile2.s> ...",
	"We can't read the file",
	"the format of the file is wrong",
	"Error at the header",
	"Syntax Error at line",
	"label doesn't exist : ",
	"We can't create the file *.cor"
};

void	ft_errors_management(t_list *files, t_file *file, char *str, int index)
{
	if (file)
		ft_printf("[%s] ", file->name);
	ft_printf("%s", g_messages[index]);
	if (str)
		ft_printf(" : \"%s\"", str);
	ft_printf("\n");
	free_data(files);
	exit(1);
}