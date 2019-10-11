/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:22:51 by hmney             #+#    #+#             */
/*   Updated: 2018/11/09 17:43:02 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 32
# include <unistd.h>
# include "libft.h"

typedef struct		s_stock
{
	int				fd;
	char			*data;
	struct s_stock	*next;
}					t_stock;

typedef struct		s_gnl
{
	char			*buf;
	char			*temp_free;
	int				index;
	int				ret;
}					t_gnl;

int					get_next_line(const int fd, char **line);

#endif
