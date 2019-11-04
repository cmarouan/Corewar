/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_bytecode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:22:12 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 13:44:33 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	create_file(char *file_name, int length, int set)
{
	char	*str;
	char	*temp;
	int		fd;

	if (set && (!(temp = ft_strsub(file_name, 0, length - 1)) ||
			!(str = ft_strjoin(temp, "cor"))))
		return (0);
	else if (!set && (!(temp = ft_strsub(file_name, 0, length - 3)) ||
			!(str = ft_strjoin(temp, "s"))))
		return (0);
	ft_strdel(&temp);
	if ((fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		return (0);
	ft_printf("Writing output program to %s\n", str);
	ft_strdel(&str);
	return (fd);
}

int	convert_bytecode(t_file *file)
{
	int	fd;

	if (!(fd = create_file(file->name, ft_strlen(file->name), 1)))
		return (0);
	file->header.magic = COREWAR_EXEC_MAGIC;
	ft_putbits_fd((char *)&file->header.magic, 4, fd);
	write(fd, file->header.prog_name, PROG_NAME_LENGTH);
	ft_putbits_fd((char *)&file->header.null, 4, fd);
	ft_putbits_fd((char *)&file->header.prog_size, 4, fd);
	write(fd, file->header.comment, COMMENT_LENGTH);
	ft_putbits_fd((char *)&file->header.null, 4, fd);
	champion_exec_code(file, fd);
	return (1);
}
