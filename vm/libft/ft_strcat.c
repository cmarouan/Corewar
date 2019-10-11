/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 12:05:06 by hmney             #+#    #+#             */
/*   Updated: 2018/10/12 10:52:00 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t index;
	size_t dest_length;

	index = -1;
	dest_length = ft_strlen((const char *)dest);
	while (src[++index] != '\0')
		dest[dest_length + index] = src[index];
	dest[dest_length + index] = '\0';
	return (dest);
}
