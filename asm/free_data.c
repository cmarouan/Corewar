/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:03:07 by hmney             #+#    #+#             */
/*   Updated: 2019/10/09 18:20:01 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void ft_delete_tokens(t_list **tokens)
{
    t_list *head;
    t_list  *temp;
    t_token *token;

    head = *tokens;
    while (head)
    {
        token = (t_token *)head->content;
        ft_strdel(&token->label);
        ft_strdel(&token->instruction);
        ft_strdel(&token->args[0]);
        ft_strdel(&token->args[1]);
        ft_strdel(&token->args[2]);
        ft_memdel((void **)&token);
        temp = head;
        head = head->next;
        ft_memdel((void **)&temp);
    }
}

static void free_content_files(t_list *files)
{
    t_list  *head;
    t_list  *temp;
    t_file  *file;
    int     index;

    head = files;
    while (head != NULL)
    {
        file = (t_file *)head->content;
        ft_strdel(&file->name);
        ft_strdel(&file->content);
        index = -1;
        while (file->code[++index])
            ft_strdel(&file->code[index]);
        ft_memdel((void **)&file->code);
        ft_lstdel(&file->labels_call ,&ft_delete_node);
        ft_lstdel(&file->labels_definition ,&ft_delete_node);
        ft_delete_tokens(&file->tokens);
        ft_memdel((void **)&file);
        temp = head;
        head = head->next;
        ft_memdel((void **)&temp);
    }
}

void free_data(t_asm *store)
{
    free_content_files(store->files);
    ft_memdel((void **)&store);
}