/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:57:20 by hmney             #+#    #+#             */
/*   Updated: 2019/10/07 10:44:00 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		start;
	int		end;

	if (s)
	{
		start = 0;
		end = ft_strlen(s) - 1;
		while (s[start] != '\0' && whitespace(s[start]))
			start++;
		while (end > start && s[end] && whitespace(s[end]))
			end--;
		str = ft_strsub(s, start, end - start + 1);
		return (str);
	}
	return (NULL);
}