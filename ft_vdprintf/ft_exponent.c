/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exponent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 08:22:56 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:12:11 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

char	*ft_exponent(int base, unsigned int exponent)
{
	char	*result;
	char	*number;
	char	*tmp_result;
	int		index;

	if (exponent == 1)
		return (ft_itoa(base));
	else if (exponent == 0)
		return (ft_strdup("1"));
	number = ft_itoa(base);
	while (--exponent)
	{
		index = 0;
		result = ft_strdup("0");
		while (index++ < base)
		{
			tmp_result = result;
			result = ft_addition(tmp_result, number);
			free(tmp_result);
		}
		free(number);
		number = ft_strdup(result);
		free(result);
	}
	return (number);
}
