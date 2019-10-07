/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:34:15 by hmney             #+#    #+#             */
/*   Updated: 2019/10/07 21:16:27 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

int lexer(t_asm *store, t_file *file)
{
    char    *str;
    int     index;

    index = -1;
    while (file->code[++index])
    {
        if (!(str = ft_strtrim(file->code[index])))
            return (0);
        if (!*str || str[0] == COMMENT_CHAR || str[0] == ALT_COMMENT_CHAR)
        {
            ft_strdel(&str);
            continue ;
        }
        if (!(header_checker(file, str, &index)))
            ft_errors_management(store, 2, index + 1);
        if (!(statement_checker(file, str, &index)))
            ft_errors_management(store, 2, index + 1);
    }
    t_list *head;
    head = file->tokens;
    while (head)
    {
        t_token *token;
        token = (t_token *)head->content;
        printf("[label: %s | cmd: %s | arg1: %s | arg2: %s | arg3: %s]\n",token->label, token->instruction, token->arg1, token->arg2, token->arg3);
        head = head->next;
    }
    return (1);
}