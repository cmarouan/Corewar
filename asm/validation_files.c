/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:03:04 by hmney             #+#    #+#             */
/*   Updated: 2019/10/08 16:40:10 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int validation_files(t_asm *store, int argc, char **argv)
{
    t_list *head;
    t_file *file;

    if (!(read_files(store, argc, argv)))
        ft_errors_management(store, NULL, 1);
    head = store->files;
    while (head)
    {
        file = (t_file *)head->content;
        lexer(store, file);
        // convert_bytecode();
        head = head->next;
    }
    return (1);
}