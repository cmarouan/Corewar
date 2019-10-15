/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:56:32 by hmney             #+#    #+#             */
/*   Updated: 2019/10/15 19:04:10 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	type_register(t_token *token, char *arg, int num_arg)
{
	int number;

	if (ft_strlen(arg) > 3 || !ft_isnumber(arg + 1) ||
			(number = ft_atoi(arg + 1)) < 0 || number > REG_NUMBER)
		return (0);
	token->args[num_arg].type_arg = T_REG;
	token->args[num_arg].code_arg = REG_CODE;
	token->args[num_arg].label_index = -1;
	return (T_REG);
}

static int	type_direct(t_file *file, t_token *token, char *arg, int num_arg)
{
	t_list *new;

	if (ft_strlen(arg) < 2)
		return (0);
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
		if (arg[1] == '+' || (arg[1] == '-' ? !ft_isnumber(arg + 2) : !ft_isnumber(arg + 1)))
			return (0);
		token->args[num_arg].label_index = -1;
	}
	token->args[num_arg].type_arg = T_DIR;
	token->args[num_arg].code_arg = DIR_CODE;
	return (T_DIR);
}

static int	type_indirect(t_file *file, t_token *token, char *arg, int num_arg)
{
	t_list *new;

	if (ft_strlen(arg) < 1)
		return (0);
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
		if (arg[0] == '+' || (arg[0] == '-' ? !ft_isnumber(arg + 1) : !ft_isnumber(arg)))
			return (0);
		token->args[num_arg].label_index = -1;
	}
	token->args[num_arg].type_arg = T_IND;
	token->args[num_arg].code_arg = IND_CODE;
	return (T_IND);
}

static int	check_args(t_file *file, t_token *token, char *arg, int num_arg)
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
	if (!(type_arg & op_tab[op_index].type_argument[num_arg]))
		return (0);
	return (type_arg);
}

int			get_args(t_file *file, t_token *token, char *str, int *index)
{
	char	**args;
	char	*arg;
	int		index2;
	int		index3;

	if (!(args = ft_strsplit(str + *index, SEPARATOR_CHAR)))
		return (0);
	token->nb_arg = ft_tablen(args);
	if ((index2 = check_instruction(token->instruction)) < 0
			|| token->nb_arg != op_tab[index2].number_registries ||
			!(token->args = (t_args *)ft_memalloc(sizeof(t_args) * token->nb_arg)))
	{
		free_tab(&args);
		return (0);
	}
	index3 = -1;
	while (++index3 < token->nb_arg)
	{
		if (!(arg = ft_strtrim(args[index3])) || !check_args(file, token, arg, index3))
		{
			free_tab(&args);
			return (0);
		}
		token->args[index3].arg = arg;
	}
	free_tab(&args);
	return (1);
}
