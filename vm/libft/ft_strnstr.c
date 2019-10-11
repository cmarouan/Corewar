/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 12:10:31 by hmney             #+#    #+#             */
/*   Updated: 2018/10/10 21:25:38 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *string, const char *substring, size_t len)
{
	unsigned int	length;

	length = ft_strlen(substring);
	if (length == 0)
		return ((char *)string);
	while (*string && len-- >= length)
	{
		if (ft_strncmp(string, substring, length) == 0)
			return ((char *)string);
		string++;
	}
	return (NULL);
}
