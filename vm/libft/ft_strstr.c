/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 20:12:25 by hmney             #+#    #+#             */
/*   Updated: 2018/10/10 19:11:52 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *string, const char *substring)
{
	size_t len;

	len = ft_strlen(substring);
	if (len == 0)
		return ((char *)string);
	while (*string)
	{
		if (ft_strncmp(string, substring, len) == 0)
			return ((char *)string);
		string++;
	}
	return (NULL);
}
