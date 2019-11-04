/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:03:07 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 12:06:35 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_content_file(t_file *file)
{
	int	index;
	int	index2;

	ft_strdel(&file->name);
	ft_strdel(&file->content);
	index = -1;
	while (file->code[++index].line)
	{
		ft_strdel(&file->code[index].line);
		ft_strdel(&file->code[index].label->name);
		ft_memdel((void **)&file->code[index].label);
		ft_strdel(&file->code[index].instruction);
		if (file->code[index].args)
		{
			index2 = -1;
			while (++index2 < file->code[index].nb_arg)
				ft_strdel(&file->code[index].args[index2].arg);
			ft_memdel((void **)&file->code[index].args);
		}
	}
	ft_memdel((void **)&file->code);
	ft_lstdel(&file->labels_call, &ft_delete_node);
	ft_lstdel(&file->labels_definition, &ft_delete_node);
	ft_memdel((void **)&file);
}

void		free_data(t_list *files)
{
	t_list	*head;
	t_list	*temp;
	t_file	*file;

	head = files;
	while (head != NULL)
	{
		file = (t_file *)head->content;
		temp = head;
		free_content_file(file);
		head = head->next;
		ft_memdel((void **)&temp);
	}
}
