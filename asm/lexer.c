/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:34:15 by hmney             #+#    #+#             */
/*   Updated: 2019/10/10 18:24:20 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
    to compile this shit run : gcc ../op.c get_args.c get_instructions.c get_label.c  statement_checker.c header_checker.c split_data.c validation_files.c lexer.c ft_errors_management.c free_data.c  main.c read_files.c ../libft/libft.a -I ../includes  &&  ./a.out path_of_file.s
*/

int lexer(t_asm *store, t_file *file)
{
    int     index;

    index = -1;
    if (!header_checker(file, &index))
        ft_errors_management(store, file->code[index], 2);
    if (!statement_checker(file, &index))
        ft_errors_management(store, file->code[index], 2);
    labels_exist(store, file);
    t_list *head;
    head = file->tokens;
    ft_lstrev(&head);
    while (head)
    {
        t_token *token;
        token = (t_token *)head->content;
        printf("[label: %s | instruction: %s | arg1: %s | arg2: %s | arg3: %s]\n", token->label, token->instruction, token->args[0], token->args[1], token->args[2]);
        head = head->next;
    }
    return (1);
}