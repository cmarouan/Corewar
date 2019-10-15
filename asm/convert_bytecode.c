/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_bytecode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:22:12 by hmney             #+#    #+#             */
/*   Updated: 2019/10/15 18:35:14 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	create_file(char *file_name)
{
	char	*str;
	char	*temp;
	int		index;
	int		fd;

	index = ft_strlen(file_name);
	if (!(str = ft_strsub(file_name, 0, index - 2)))
		return (0);
	temp = str;
	if (!(str = ft_strjoin(str, ".cor")))
		return (0);
	ft_strdel(&temp);
	if ((fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		return (0);
	ft_printf("Writing output program to %s\n", str);
	ft_strdel(&str);
	return (fd);
}

int			convert_bytecode(t_file *file)
{
	int	fd;

	if (!(fd = create_file(file->name)))
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
