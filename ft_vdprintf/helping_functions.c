/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 22:56:24 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:12:12 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vdprintf.h"

int		is_a_conversion_character(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
			|| c == 'o' || c == 'u' || c == 'x' || c == 'f' || c == 'b'
			|| c == 'C' || c == 'S' || c == 'P' || c == 'D' || c == 'I'
			|| c == 'O' || c == 'U' || c == 'X' || c == 'F' || c == '%');
}

int		is_a_flag(char c)
{
	return (c == '0' || c == '+' || c == '-' || c == ' ' || c == '#');
}

int		is_a_lengthmodifier(char c)
{
	return (c == 'h' || c == 'l' || c == 'z' || c == 'j' || c == 'L');
}

void	ft_print_character(t_vdprintf store, int number, int c)
{
	int i;

	i = 0;
	while (i < number)
	{
		ft_putchar_fd(c, store.fd);
		i++;
	}
}

int		get_number(char *format, int *counter)
{
	char	*number_string;
	int		number_integer;

	while (*(format + *counter) && ft_isdigit(*(format + *counter)))
		(*counter)++;
	number_string = ft_strsub(format, 0, *counter);
	number_integer = ft_atoi(number_string);
	free(number_string);
	return (number_integer < 0 ? -1 : number_integer);
}
