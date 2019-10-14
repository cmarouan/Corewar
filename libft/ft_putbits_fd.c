/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbits_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:37:14 by hmney             #+#    #+#             */
/*   Updated: 2019/10/11 15:38:10 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_putbits_fd(const char *bits, size_t size, int fd)
{
    size_t  index;

    if (size == 0)
        return ;
    index = 0;
    while (index < size)
    {
        write(fd, bits + (size - index - 1), 1);
        index++;
    }
}