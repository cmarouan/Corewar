/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:57:28 by hmney             #+#    #+#             */
/*   Updated: 2019/10/09 18:31:45 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void labels_exist(t_asm *store, t_file *file)
{
	t_list *head;
	t_list *head2;

	head = file->labels_call;
	while (head)
	{
		head2 = file->labels_definition;
		while (head2)
		{
			if (!ft_strcmp(head->content, head2->content))
				break ;
			head2 = head2->next;
		}
		if (!head2)
			ft_errors_management(store, head->content, 3);
		head = head->next;
	}
}

int check_label(char *label)
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

int get_label(t_file *file, t_token *token, char *str, int *index)
{
	t_list *new;
	int index2;

	index2 = *index;
	while (str[*index] && str[*index] != LABEL_CHAR && !ft_isblank(str[*index]) && str[*index] != DIRECT_CHAR)
		(*index)++;
	if (str[*index] == LABEL_CHAR)
	{
		if (!(token->label = ft_strsub(str, index2, (*index)++ - index2)) || !check_label(token->label))
		{
			ft_strdel(&token->label);
			return (0);
		}
		if (!(new = ft_lstnew((void *)token->label, ft_strlen(token->label) + 1)))
		{
			ft_strdel(&token->label);
			return (0);
		}
		ft_lstadd(&file->labels_definition, new);
		return (1);
	}
	else if (ft_isblank(str[*index]) || str[*index] == DIRECT_CHAR)
	{
		if (!(token->instruction = ft_strsub(str, index2, *index - index2)) || check_instruction(token->instruction) == -1)
		{
			ft_strdel(&token->instruction);
			return (0);
		}
		return (-1);
	}
	return (0);
}