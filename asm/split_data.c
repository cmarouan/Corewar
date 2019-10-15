/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:20:31 by hmney             #+#    #+#             */
/*   Updated: 2019/10/15 14:21:07 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	words(const char *str, char c)
{
	int flag_quote;
	int index;
	int counter;

	index = 0;
	if (str[index] != c)
		index++;
	counter = index;
	flag_quote = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '"')
			flag_quote = !flag_quote;
		if (!flag_quote && str[index] != c && str[index - 1] == c)
			counter++;
		index++;
	}
	return (counter);
}

static int	ft_count_char(char *str, char c)
{
	int counter;
	int flag_quote;

	counter = 0;
	flag_quote = 0;
	while (str[counter] != '\0')
	{
		if (str[counter] == '"')
			flag_quote = !flag_quote;
		if (!flag_quote && str[counter] == c)
			break ;
		counter++;
	}
	return (counter);
}

t_token		*split_data(char const *s, char c)
{
	t_token	*tab;
	int		index;
	int		size;

	index = 0;
	if (!(tab = (t_token *)ft_memalloc(sizeof(t_token) * (words(s, c) + 1))))
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			size = ft_count_char((char *)s, c);
			while (*s == c)
				s++;
			if (!(tab[index++].line = ft_strsub(s, 0, size)))
				return (NULL);
			s = s + size;
		}
		else
			s++;
	}
	tab[index].line = NULL;
	return (tab);
}
