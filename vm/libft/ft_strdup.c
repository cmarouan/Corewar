/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:24:29 by hmney             #+#    #+#             */
/*   Updated: 2018/10/12 10:46:47 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(src) + 1;
	if ((copy = (char *)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	ft_strcpy(copy, src);
	return (copy);
}
