/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:57:28 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 18:58:25 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ind_dir_labels(t_args *arg, t_label **label, t_list *head)
{
	*label = (t_label *)head->content;
	if ((arg->type_arg == T_DIR && !ft_strcmp(arg->arg + 2, (*label)->name)) ||
	((arg->type_arg == T_IND && !ft_strcmp(arg->arg + 1, (*label)->name))))
		return (1);
	return (0);
}

void		labels_exist(t_list *files, t_file *file)
{
	t_list	*head;
	t_list	*head2;
	t_label	*label;
	t_args	*arg;

	head = file->labels_call;
	while (head)
	{
		arg = (t_args *)head->content;
		head2 = file->labels_definition;
		while (head2)
		{
			if (ind_dir_labels(arg, &label, head2))
			{
				if (arg->label_index == -1)
					arg->label_index = label->index;
				break ;
			}
			head2 = head2->next;
		}
		if (!head2)
			ft_errors_management(files, file, arg->arg +
					(arg->type_arg == T_DIR ? 2 : 1), 5);
		head = head->next;
	}
}

int			check_label(char *label)
{
	int index;

	index = -1;
	while (label[++index])
	{
		if (!ft_strchr(LABEL_CHARS, label[index]))
			return (0);
	}
	return (1);
}

int			get_label(t_file *file, t_token *token, char *str, int *index)
{
	int		index2;

	index2 = *index;
	while (str[*index] && str[*index] != LABEL_CHAR && !ft_isblank(str[*index])
			&& str[*index] != DIRECT_CHAR)
		(*index)++;
	if (str[*index] == LABEL_CHAR)
	{
		if (!(token->label = (t_label *)ft_memalloc(sizeof(t_label))))
			return (0);
		if (!(token->label->name = ft_strsub(str, index2, (*index)++ - index2))
				|| !check_label(token->label->name))
			return (0);
		if (!ft_list_add_back(&file->labels_definition, (void *)token->label,
					sizeof(t_label)))
			return (0);
		return (1);
	}
	else if (ft_isblank(str[*index]) || str[*index] == DIRECT_CHAR)
		if ((token->instruction = ft_strsub(str, index2, *index - index2)) &&
				check_instruction(token->instruction) != -1)
			return (-1);
	return (0);
}
