/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:18:35 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 14:16:51 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_file	*get_content_file(char *name, char *buf, int fd)
{
	t_file	*file;
	char	*temp;
	int		ret;

	if (!(file = (t_file *)ft_memalloc(sizeof(t_file))))
		return (NULL);
	if (!(file->name = ft_strdup(name)))
		return (NULL);
	if (!(file->content = ft_strnew(0)))
		return (NULL);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		temp = file->content;
		if (!(file->content = ft_strjoin(file->content, buf)))
			return (NULL);
		ft_strdel(&temp);
	}
	if (!(file->code = split_data(file->content, '\n')))
		return (NULL);
	return (file);
}

int				check_name_file(char *str, int set)
{
	int	index;

	index = ft_strlen(str);
	if (set)
	{
		if (index < 3 || str[index - 1] != 's' || str[index - 2] != '.' ||
				str[index - 3] == '/')
			return (0);
	}
	else
	{
		if (index < 5 || ft_strcmp(str + (index - 4), ".cor") ||
				str[index - 5] == '/')
			return (0);
	}
	return (1);
}

void			read_files(t_list **files, int argc, char **argv)
{
	t_list	*new;
	t_file	*elem;
	char	*buf;
	int		index;
	int		fd;

	index = 0;
	if (!(buf = (char *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))))
		return ;
	while (++index < argc)
	{
		if (!check_name_file(argv[index], 1))
			ft_errors_management(*files, NULL, argv[index], 2);
		if ((fd = open(argv[index], O_RDONLY)) < 0)
			ft_errors_management(*files, NULL, argv[index], 1);
		if (!(elem = get_content_file(argv[index], buf, fd)))
			ft_errors_management(*files, NULL, argv[index], 1);
		if (!(new = ft_lstnew((void *)elem, sizeof(t_file))))
			ft_errors_management(*files, NULL, argv[index], 1);
		ft_lstadd(files, new);
		close(fd);
	}
	ft_strdel(&buf);
}
