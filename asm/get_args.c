/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:56:32 by hmney             #+#    #+#             */
/*   Updated: 2019/10/09 20:48:48 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_number(char *str)
{
	size_t index;

	index = 0;
	if (str[index] == '\0')
		return (0);
	while (str[index] != '\0')
	{
		if (!ft_isdigit(str[index]))
			return (0);
		index++;
	}
	return (1);
}

int type_argument(t_file *file, char *arg)
{
	t_list *new;
	int index;
	int number;
	
	index = 0;
	if (arg[0] == 'r')
	{
		if (ft_strlen(arg) > 3 || !is_number(arg + 1) || (number = ft_atoi(arg + 1)) < 1 || number > REG_NUMBER)
			return (0);
		return (T_REG);
	}
	else if (arg[0] == DIRECT_CHAR)
	{
		if (ft_strlen(arg) < 2)
			return (0);
		if (arg[1] == LABEL_CHAR)
		{
			if (!check_label(arg + 2))
				return (0);
			if (!(new = ft_lstnew((void *)arg + 2, ft_strlen(arg + 2) + 1)))
				return (0);
			ft_lstadd(&file->labels_call, new);
		}
		else
		{
			if (arg[1] == '+' || !ft_isnumber(arg + 1))
				return (0);
		}
		return (T_DIR);
	}
	else
	{
		if (ft_strlen(arg) < 1)
			return (0);
		if (arg[0] == LABEL_CHAR)
		{
			if (!check_label(arg + 1))
				return (0);
			if (!(new = ft_lstnew((void *)arg + 1, ft_strlen(arg + 1) + 1)))
				return (0);
			ft_lstadd(&file->labels_call, new);
		}
		else
		{
			if (arg[0] == '+' || !ft_isnumber(arg + 1))
				return (0);
		}
		return (T_IND);
	}
	return (0);
}

int check_args(t_file *file, char *arg, int num_arg, int op_index)
{
	int type_arg;
	
	type_arg = type_argument(file, arg);
	if (!(type_arg & op_tab[op_index].type_argument[num_arg]))
		return (0);
	return (1);
}

int get_args(t_file *file, t_token *token, char *str, int *index)
{
	char    **args;
	char	*arg;
	int     length;
	int		index2;
	int		index3;

	if (!(args = ft_strsplit(str + *index, ',')))
		return (0);
	length = ft_tablen(args);
	if ((index2 = check_instruction(token->instruction)) == -1)
	{
        free_tab(&args);
		return (0);
    }
	if (length != op_tab[index2].number_registries)
    {
        free_tab(&args);
		return (0);
    }
	index3 = -1;
	while (++index3 < length)
	{
		if (!(arg = ft_strtrim(args[index3])))
		{
			free_tab(&args);
			return (0);
		}
		if (!check_args(file, arg, index3, index2))
		{
			ft_strdel(&arg);
			free_tab(&args);
			return (0);
		}
		token->args[index3] = arg;
	}
    free_tab(&args);
	return (1);
}