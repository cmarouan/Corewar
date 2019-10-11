/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 22:48:29 by hmney             #+#    #+#             */
/*   Updated: 2018/10/10 23:04:31 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t len;

	len = ft_strlen(str) + 1;
	while (len--)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		else
			str++;
	}
	return (NULL);
}
