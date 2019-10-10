/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:34:15 by hmney             #+#    #+#             */
/*   Updated: 2019/10/10 14:21:07 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int lexer(t_asm *store, t_file *file)
{
    int     index;

    index = -1;
    if (!header_checker(file, &index))
        ft_errors_management(store, file->code[index], 2);
    if (!statement_checker(file, &index))
        ft_errors_management(store, file->code[index], 2);
    labels_exist(store, file);
    return (1);
}