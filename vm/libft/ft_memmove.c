/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:51:54 by hmney             #+#    #+#             */
/*   Updated: 2018/10/12 10:25:21 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	char		*s1;
	const char	*s2;
	char		*temp;

	s1 = (char *)str1;
	s2 = (const char *)str2;
	if ((temp = (char *)malloc(sizeof(char) * n)) == NULL)
		return (NULL);
	ft_memcpy(temp, s2, n);
	ft_memcpy(s1, temp, n);
	return (s1);
}
