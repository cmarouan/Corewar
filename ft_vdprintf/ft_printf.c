/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:04:33 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:33:17 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

int ft_printf(const char * restrict format, ...)
{
    va_list		ap;
    int         ret;
    
    va_start(ap, format);
    ret = ft_vdprintf(1, format, ap);
    va_end(ap);
    return (ret);
}