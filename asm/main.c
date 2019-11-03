/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:13:11 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 19:43:29 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int read_bytes(char *file_name, int fd_read)
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

	index = 2;
	if (index < argc)
	{
		while (index < argc)
		{
			if (!check_name_file(argv[index], 0))
			{
				ft_printf("the format of the file is wrong: %s", argv[index]);
				break ;
			}
			if (!(fd = open(argv[index], O_RDONLY)))
				return ;
			read_bytes(argv[index], fd);
			index++;
		}
	}
	else
		ft_printf("Error number of file\n");
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
