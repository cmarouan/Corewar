/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:34:15 by hmney             #+#    #+#             */
/*   Updated: 2019/11/05 11:28:49 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	lexer(t_list *files, t_file *file)
{
	int	index;

	index = -1;
	if (!header_checker(file, &index))
		ft_errors_management(files, file, file->code[index].line, 3);
	if (!file->code[index].line || !statement_checker(file, &index))
		ft_errors_management(files, file, file->code[index].line, 4);
	labels_exist(files, file);
	index = -1;
	return (1);
}
