/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:13:11 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 23:27:59 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int read_byte_code(char *file_name, int fd_read)
{
	t_header header;
	int fd_write;

	if (!(fd_write = create_file(file_name, 0)))
		return (0);
	if (!create_header(header, fd_read, fd_write))
		return (0);
	if (!create_assembly_code(fd_read, fd_write))
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
			{
				ft_printf("the format of the file is wrong: %s", argv[index]);
				exit(1);
			}
			if (!(fd = open(argv[index], O_RDONLY)))
			{
				ft_printf("We can't read the file: %s\n", argv[index]);
				exit(1);
			}
			if (!read_byte_code(argv[index], fd))
			{
				ft_printf("We can't read the file: %s\n", argv[index]);
				exit(1);
			}
		}
	}
	else
		ft_printf("     Usage: ./asm [-d] <sourcefile1.s> <sourcefile2.s> ...\n");
}

static void assembler(t_list *files, int argc, char **argv)
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

int	main(int argc, char **argv)
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
