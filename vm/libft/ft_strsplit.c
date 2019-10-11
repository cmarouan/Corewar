/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 21:09:57 by hmney             #+#    #+#             */
/*   Updated: 2019/10/08 09:51:27 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words(const char *str, char c)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	if (str[i] != c)
	{
		counter++;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i - 1] == c)
			counter++;
		i++;
	}
	return (counter);
}

static int	ft_count_char(char *str, char c)
{
	int counter;

	counter = 0;
	while (str[counter] != '\0' && str[counter] != c)
		counter++;
	return (counter);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		j;
	int		size;

	j = 0;
	if ((tab = (char **)malloc(sizeof(char *) * (words(s, c) + 1))) == NULL)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			size = ft_count_char((char *)s, c);
			while (*s == c)
				s++;
			if (!(tab[j++] = ft_strsub(s, 0, size)))
				return (NULL);
			s = s + size;
		}
		else
			s++;
	}
	tab[j] = 0;
	return (tab);
}
