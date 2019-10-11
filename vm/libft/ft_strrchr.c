/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 23:08:34 by hmney             #+#    #+#             */
/*   Updated: 2018/10/12 11:01:37 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;
	size_t	i;
	int		j;

	len = ft_strlen(str) + 1;
	i = 0;
	j = -1;
	while (i < len)
	{
		if (str[i] == (unsigned char)c)
			j = (int)i;
		i++;
	}
	if (j != -1)
		return ((char *)(str + j));
	return (NULL);
}
