/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statement_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:35:14 by hmney             #+#    #+#             */
/*   Updated: 2019/11/05 11:34:32 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_token(t_file *file, t_token *token, char *str)
{
	int	index;
	int	ret;

	index = 0;
	if (!(ret = get_label(file, token, str, &index)))
		return (0);
	else if (ret == 1)
	{
		if (!(ret = get_instruction(token, str, &index)))
			return (0);
	}
	if (ret == -1 && !get_args(file, token, str, &index))
		return (0);
	return (1);
}

static int	calcul_number_byte(t_token *token)
{
	int result;
	int index;
	int index2;

	result = 1;
	index = check_instruction(token->instruction);
	result += (g_op_tab[index].argument_type_code) ? 1 : 0;
	index2 = -1;
	while (++index2 < token->nb_arg)
	{
		if (token->args[index2].type_arg & T_REG)
			result++;
		if (token->args[index2].type_arg & T_DIR)
			result += (g_op_tab[index].changes_carry) ? 2 : 4;
		if (token->args[index2].type_arg & T_IND)
			result += 2;
	}
	token->number_byte = result;
	return (result);
}

static void	noname(t_file *file, int index)
{
	if (file->code[index].label)
		file->code[index].label->index = index;
	if (file->code[index].instruction)
		file->header.prog_size += calcul_number_byte(&file->code[index]);
}

int			statement_checker(t_file *file, int *index)
{
	char	*str;

	(*index)--;
	while (file->code[++(*index)].line)
	{
		if (!(str = check_comment(file->code[*index].line)))
			return (0);
		if (file->code[*index + 1].line == NULL &&
				file->content[ft_strlen(file->content) - 1] != '\n' && *str)
			return (0);
		if (!*str || str[0] == COMMENT_CHAR || str[0] == ALT_COMMENT_CHAR)
		{
			ft_strdel(&str);
			continue ;
		}
		if (!get_token(file, &file->code[*index], str))
		{
			ft_strdel(&str);
			return (0);
		}
		noname(file, *index);
		ft_strdel(&str);
	}
	return (1);
}
