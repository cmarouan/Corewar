/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:13:11 by hmney             #+#    #+#             */
/*   Updated: 2019/10/16 19:25:10 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int16_t swap_int16(int16_t value) 
{
    return ((value << 8) | ((value >> 8) & 0xFF));
}

int32_t swap_int32(int32_t value)
{
    value = (((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF)); 
    return ((value << 16) | ((value >> 16) & 0xFFFF));
}

int create_header(int fd_read, int fd_write)
{
	char name[PROG_NAME_LENGTH + 1];
	char comment[COMMENT_LENGTH + 1];
	int bytes;
	
	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0)
		return (0);
	if (read(fd_read, name, PROG_NAME_LENGTH) < 0)
		return (0);
	dprintf(fd_write, "%s \"%s\"\n",NAME_CMD_STRING, name);
	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0)
		return (0);
	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0)
		return (0);
	if (read(fd_read, comment, COMMENT_LENGTH) < 0)
		return (0);
	dprintf(fd_write, "%s \"%s\"\n\n",COMMENT_CMD_STRING, comment);
	bytes = 0;
	if (read(fd_read, &bytes, 4) < 0)
		return (0);
	return (1);
}

int create_assembly_code(int fd_read, int fd_write)
{
	int op_code;
	int arg_type;
	int	args[3];
	int index;
	int shift;
	unsigned int value;

	op_code = 0;
	// change
	for(int i=0;i<3;i++)
        args[i] = 0;
	// change
	while (read(fd_read, &op_code, 1) > 0)
	{
		if (op_code < 1 || op_code > 16)
			return (0);
		dprintf(fd_write, "%s ", op_tab[op_code - 1].instruction);
		arg_type = 0;
		if (op_tab[op_code - 1].argument_type_code)
		{
			if (read(fd_read, &arg_type, 1) < 0)
				return (0);
			index = -1;
			shift = 6;
			while (++index < op_tab[op_code - 1].number_registries)
			{
				args[index] = arg_type >> shift;
				arg_type ^= args[index] << shift;
				shift -= 2;
			}
			index = -1;
			while (++index < op_tab[op_code - 1].number_registries)
			{
				value = 0;
				if (args[index] == 0)
					break ;
				if (args[index] & REG_CODE)
				{
					if (read(fd_read, &value, 1) < 0)
						return (0);
					dprintf(fd_write, "r%d", value);
					if (index + 1 != op_tab[op_code - 1].number_registries)
						dprintf(fd_write, ", ");
				}
				else if (args[index] & DIR_CODE)
				{
					int byte = (op_tab[op_code - 1].changes_carry ? 2 : 4);
					if (read(fd_read, &value, byte) < 0)
						return (0);
					if (byte == 2)
						dprintf(fd_write, "%%%d", swap_int16((int16_t)value));
					else
						dprintf(fd_write, "%%%d",swap_int32((int32_t)value));
					if (index + 1 != op_tab[op_code - 1].number_registries)
						dprintf(fd_write, ", ");
				}
				else if (args[index] & IND_CODE)
				{
					if (read(fd_read, &value, 2) < 0)
						return (0);
					dprintf(fd_write, "%d",value);
					if (index + 1 != op_tab[op_code - 1].number_registries)
						dprintf(fd_write, ", ");
				}
			}
		}
		else
		{
			index = -1;
			while (++index < op_tab[op_code - 1].number_registries)
			{
				value = 0;
				if (op_tab[op_code - 1].type_argument[0] & REG_CODE)
				{
					if (read(fd_read, &value, 1) < 0)
						return (0);
					dprintf(fd_write, "r%d", value);
					if (index + 1 != op_tab[op_code - 1].number_registries)
						dprintf(fd_write, ", ");
				}
				else if (op_tab[op_code - 1].type_argument[0] & DIR_CODE)
				{
					int byte = (op_tab[op_code - 1].changes_carry ? 2 : 4);
					if (read(fd_read, &value, byte) < 0)
						return (0);
					if (byte == 2)
						dprintf(fd_write, "%%%d", swap_int16((int16_t)value));
					else
						dprintf(fd_write, "%%%d",swap_int32((int32_t)value));
					if (index + 1 != op_tab[op_code - 1].number_registries)
						dprintf(fd_write, ", ");
				}
				else if (op_tab[op_code - 1].type_argument[0] & IND_CODE)
				{
					if (read(fd_read, &value, 2) < 0)
						return (0);
					dprintf(fd_write, "%d",value);
					if (index + 1 != op_tab[op_code - 1].number_registries)
						dprintf(fd_write, ", ");
				}
			}
			
		}
		dprintf(fd_write, "\n");
	}
	return (1);
}

int read_bytes(char *file_name, int fd_read)
{
	int fd_write;
	
	if (!(fd_write = create_file(file_name, 0)))
		return (0);
	if (!create_header(fd_read, fd_write))
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
