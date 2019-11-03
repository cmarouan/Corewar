/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 08:25:28 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:12:12 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

int		calcul_empty_space(char *number)
{
	int counter;

	counter = 0;
	while (number[counter] != '\0' && number[counter] == '-')
		counter++;
	return (counter);
}

int		length_float(t_vdprintf *store, t_float *float_data, int length_data)
{
	int length_final;

	if (store->precision > length_data)
		length_final = store->precision + 1;
	else
		length_final = length_data;
	if (float_data->comma <= 0)
		length_final += 1 - float_data->comma;
	else
		length_final += float_data->comma;
	if (length_final < 0)
	{
		length_final = store->precision;
		store->precision = -1;
	}
	return (length_final);
}

void	delete_empty_space(char **number)
{
	char	*result;
	char	*tmp;
	int		length;
	int		index;
	int		index2;

	index = calcul_empty_space(*number);
	length = ft_strlen(*number) - index;
	if (!(result = ft_strnew(length)))
		return ;
	index2 = 0;
	while ((*number)[index] != '\0')
		result[index2++] = (*number)[index++];
	tmp = *number;
	*number = result;
	free(tmp);
}

char	*add_zeros(t_float float_data, char *data, int l_data, int l_final)
{
	char	*result;
	int		index;
	int		index2;

	if (!(result = ft_strnew(l_final)))
		return (NULL);
	index = 0;
	if (float_data.comma <= 0)
		result[index++] = '0';
	index2 = (float_data.comma < 0) ? -float_data.comma : 0;
	while (index < l_final && index2--)
		result[index++] = '0';
	index2 = 0;
	while (l_data--)
		result[index++] = data[index2++];
	while (index < l_final)
		result[index++] = '0';
	return (result);
}

char	*calcul_fd_specialcase(t_vdprintf store, t_float float_data)
{
	char *result;

	if (float_data.mantissa_number == 0)
	{
		if (store.conversion_character == 'f')
			result = ft_strdup("inf");
		else
			result = ft_strdup("INF");
	}
	else
	{
		if (store.conversion_character == 'f')
			result = ft_strdup("nan");
		else
			result = ft_strdup("NAN");
	}
	return (result);
}
