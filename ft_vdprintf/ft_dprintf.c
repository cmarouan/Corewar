/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:11:01 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:24:28 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

int ft_dprintf(int fd, const char *format, ...)
{
    va_list		ap;
    int         ret;
    
    va_start(ap, format);
    ret = ft_vdprintf(fd, format, ap);
    va_end(ap);
    return (ret);
}