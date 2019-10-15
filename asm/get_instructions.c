/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:57:08 by hmney             #+#    #+#             */
/*   Updated: 2019/10/15 14:14:39 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	check_instruction(char *instruction)
{
	int index;

	index = -1;
	while (++index < 16)
	{
		if (!ft_strcmp(instruction, op_tab[index].instruction))
			return (index);
	}
	return (-1);
}

int	get_instruction(t_token *token, char *str, int *index)
{
	int index2;

	while (str[*index] && ft_isblank(str[*index]))
		(*index)++;
	index2 = *index;
	if (!str[*index])
		return (1);
	while (str[*index] && !ft_isblank(str[*index]) &&
			str[*index] != DIRECT_CHAR)
		(*index)++;
	if (!(token->instruction = ft_strsub(str, index2, *index - index2))
			|| check_instruction(token->instruction) == -1)
		return (0);
	return (-1);
}
