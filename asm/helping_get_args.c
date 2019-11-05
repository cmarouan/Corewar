/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_get_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:10:21 by hmney             #+#    #+#             */
/*   Updated: 2019/11/05 12:41:44 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	type_register(t_token *token, char *arg, int num_arg)
{
	int number;

	if (ft_strlen(arg) > 3 || !ft_isnumber(arg + 1) ||
			(number = ft_atoi(arg + 1)) <= 0 || number > REG_NUMBER)
		return (0);
	token->args[num_arg].type_arg = T_REG;
	token->args[num_arg].code_arg = REG_CODE;
	token->args[num_arg].label_index = -1;
	return (T_REG);
}

int	type_direct(t_file *file, t_token *token, char *arg, int num_arg)
{
	t_list *new;

	if (ft_strlen(arg) < 2)
		return (0);
	token->args[num_arg].label_index = -1;
	token->args[num_arg].type_arg = T_DIR;
	token->args[num_arg].code_arg = DIR_CODE;
	if (arg[1] == LABEL_CHAR)
	{
		if (!check_label(arg + 2))
			return (0);
		if (!(new = ft_lstnew((void *)&token->args[num_arg], sizeof(t_args))))
			return (0);
		ft_lstadd(&file->labels_call, new);
	}
	else
	{
		if (arg[1] == '+' || (arg[1] == '-' ? !ft_isnumber(arg + 2) :
					!ft_isnumber(arg + 1)))
			return (0);
	}
	return (T_DIR);
}

int	type_indirect(t_file *file, t_token *token, char *arg, int num_arg)
{
	t_list *new;

	if (ft_strlen(arg) < 1)
		return (0);
	token->args[num_arg].label_index = -1;
	token->args[num_arg].type_arg = T_IND;
	token->args[num_arg].code_arg = IND_CODE;
	if (arg[0] == LABEL_CHAR)
	{
		if (!check_label(arg + 1))
			return (0);
		if (!(new = ft_lstnew((void *)&token->args[num_arg], sizeof(t_args))))
			return (0);
		ft_lstadd(&file->labels_call, new);
	}
	else
	{
		if (arg[0] == '+' || (arg[0] == '-' ? !ft_isnumber(arg + 1) :
					!ft_isnumber(arg)))
			return (0);
	}
	return (T_IND);
}

int	check_args(t_file *file, t_token *token, char *arg, int num_arg)
{
	int type_arg;
	int op_index;

	if ((op_index = check_instruction(token->instruction)) == -1)
		return (0);
	if (arg[0] == 'r')
		type_arg = type_register(token, arg, num_arg);
	else if (arg[0] == DIRECT_CHAR)
		type_arg = type_direct(file, token, arg, num_arg);
	else
		type_arg = type_indirect(file, token, arg, num_arg);
	if (!(type_arg & g_op_tab[op_index].type_argument[num_arg]))
		return (0);
	return (type_arg);
}

int	check_args2(t_token *token, char **args, char *str)
{
	int index;
	int index2;

	if ((index = check_instruction(token->instruction)) < 0)
		return (0);
	if ((token->nb_arg = ft_tablen(args)) != g_op_tab[index].number_registries)
		return (0);
	if ((index2 = ft_search_characters(str, SEPARATOR_CHAR)) !=
			g_op_tab[index].number_registries - 1)
		return (0);
	if (!(token->args = (t_args *)ft_memalloc(sizeof(t_args) * token->nb_arg)))
		return (0);
	return (1);
}
