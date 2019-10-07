/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 09:59:04 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 10:01:16 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_hash_string(char *str)
{
	intmax_t	hash_value;
	intmax_t	p_pow;
	int			p;
	int			mod;
	int			index;

	p = 53;
	mod = 1e9 + 9;
	hash_value = 0;
	p_pow = 1;
	index = -1;
	while (str[++index])
	{
		hash_value = (hash_value + (str[index] + 1) * p_pow) % mod;
		p_pow = (p_pow * p) % mod;
	}
	return (hash_value);
}
