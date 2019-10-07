/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:03:07 by hmney             #+#    #+#             */
/*   Updated: 2019/10/07 15:26:09 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void free_content_files(t_list **files)
{
    t_list  *head;
    t_list  *temp;
    t_file  *file;
    int     index;

    head = *files;
    while (head != NULL)
    {
        file = (t_file *)head->content;
        ft_strdel(&file->name);
        ft_strdel(&file->content);
        index = -1;
        while (file->code[++index])
            ft_strdel(&file->code[index]);
        ft_memdel((void **)&file->code);
        ft_memdel((void **)&file);
        temp = head;
        head = head->next;
        ft_memdel((void **)&temp);
    }
}

void free_data(t_asm *store)
{
    free_content_files(&store->files);
    ft_memdel((void **)&store);
}