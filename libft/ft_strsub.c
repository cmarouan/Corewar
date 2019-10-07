/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:50:54 by hmney             #+#    #+#             */
/*   Updated: 2018/10/12 11:42:37 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	int		temp;

	if (s)
	{
		i = 0;
		temp = start;
		while (s[temp++] != '\0' && i != len)
			i++;
		if (i != len)
			return (NULL);
		i = 0;
		if ((sub = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
			return (NULL);
		while (len--)
			sub[i++] = s[start++];
		sub[i] = '\0';
		return (sub);
	}
	return (NULL);
}
