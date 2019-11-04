/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:13:11 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 20:21:37 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	read_byte_code(char *file_name, int fd_read)
{
	t_header	header;
	int			fd_write;

	if (!(fd_write = create_file(file_name, ft_strlen(file_name), 0)))
		return (0);
	if (!read_header(header, fd_read, fd_write))
		return (0);
	if (!read_assembly_code(fd_read, fd_write))
		return (0);
	return (1);
}

static void	disassembler(int argc, char **argv)
{
	int index;
	int fd;

	index = 1;
	if (index + 1 < argc)
	{
		while (++index < argc)
		{
			if (!check_name_file(argv[index], 0))
				ft_errors_management2(argv[index], 0);
			if ((fd = open(argv[index], O_RDONLY)) < 0)
				ft_errors_management2(argv[index], 1);
			if (!read_byte_code(argv[index], fd))
				ft_errors_management2(argv[index], 2);
		}
	}
	else
		ft_errors_management2(NULL, 3);
}

static void	assembler(t_list *files, int argc, char **argv)
{
	t_list *head;
	t_file *file;

	read_files(&files, argc, argv);
	head = files;
	while (head)
	{
		file = (t_file *)head->content;
		lexer(files, file);
		if (!convert_bytecode(file))
			ft_errors_management(files, file, NULL, 6);
		head = head->next;
	}
	free_data(files);
}

int			main(int argc, char **argv)
{
	t_list *files;

	files = NULL;
	if (argc == 1)
		ft_errors_management(files, NULL, NULL, 0);
	if (!ft_strcmp(argv[1], "-d"))
		disassembler(argc, argv);
	else
		assembler(files, argc, argv);
	return (0);
}
