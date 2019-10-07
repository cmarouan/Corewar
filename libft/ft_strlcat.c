/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 21:49:51 by hmney             #+#    #+#             */
/*   Updated: 2018/10/10 22:34:00 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dst_len;
	size_t src_len;
	size_t result;

	dst_len = ft_strlen((const char *)dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		result = size + src_len;
	else
	{
		ft_strncat(dst, src, size - dst_len - 1);
		result = dst_len + src_len;
	}
	return (result);
}
