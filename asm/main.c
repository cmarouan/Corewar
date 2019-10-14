/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:13:11 by hmney             #+#    #+#             */
/*   Updated: 2019/10/14 23:49:42 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int argc, char **argv)
{
    t_list *files;
    t_list *head;
    t_file *file;

    files = NULL;
    if (argc == 1)
        ft_errors_management(files, NULL, NULL, 0);
    read_files(&files, argc, argv);
    head = files;
    while (head)
    {
        file = (t_file *)head->content;
        lexer(files, file);
        if (!convert_bytecode(files, file))
            ft_errors_management(files, file, NULL, 6);
        head = head->next;
    }
    free_data(files);
    return (0);
}