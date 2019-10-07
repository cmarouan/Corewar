/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 21:34:54 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 11:50:42 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		search(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	return (-1);
}

static t_stock	*get_stock(const int fd, t_stock **list)
{
	t_stock *temp;
	t_stock *new;

	temp = *list;
	while (temp != NULL && temp->fd != fd)
		temp = temp->next;
	if (temp != NULL)
		return (temp);
	if (!(new = (t_stock *)malloc(sizeof(t_stock))))
		return (NULL);
	new->fd = fd;
	new->data = ft_strnew(0);
	new->next = *list;
	*list = new;
	return (new);
}

static void		free_stock(t_stock *stock)
{
	t_stock *temp;

	while (stock != NULL)
	{
		temp = stock;
		ft_strdel(&temp->data);
		stock = stock->next;
		ft_memdel((void **)&temp);
	}
}

static int		get_line(t_stock *fds, t_stock *stock, char **line, t_gnl env)
{
	if (env.ret < 0)
		return (-1);
	if (env.ret == 0 && !*stock->data)
	{
		free_stock(fds);
		return (0);
	}
	if (env.index != -1)
	{
		*line = ft_strsub(stock->data, 0, env.index);
		ft_strcpy(stock->data, stock->data + env.index + 1);
	}
	else
	{
		*line = stock->data;
		stock->data = ft_strnew(0);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_stock	*fds = NULL;
	t_stock			*stock;
	t_gnl			env;

	if (fd < 0 || fd > 4096 || line == NULL)
		return (-1);
	if (!(env.buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	stock = get_stock(fd, &fds);
	env.ret = 0;
	if ((env.index = search(stock->data)) == -1)
	{
		while ((env.ret = read(fd, env.buf, BUFF_SIZE)) > 0)
		{
			env.buf[env.ret] = '\0';
			env.temp_free = stock->data;
			stock->data = ft_strjoin(stock->data, env.buf);
			ft_strdel(&env.temp_free);
			if ((env.index = search(stock->data)) != -1)
				break ;
		}
	}
	ft_strdel(&env.buf);
	return (get_line(fds, stock, line, env));
}
