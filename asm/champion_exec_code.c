/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_exec_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 23:10:48 by hmney             #+#    #+#             */
/*   Updated: 2019/10/14 20:24:34 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int noname(t_file *file, int src, int dst)
{
    int result;
    int sign;
    
    result = 0;
    sign = 1;
    if (src < dst)
    {
        while (src < dst)
        {
            result += file->code[src].number_byte;
            src++;
        }
    }
    else
    {
        sign = -1;
        while (src-- > dst)
        {
            result += file->code[src].number_byte;
        }
    }
    return (result * sign);
}


int get_argument_type(t_token *token)
{
    int number;
    int index;
    int shift;

    index = -1;
    shift = 6;
    number = 0;
    while (++index < token->nb_arg)
    {
        number |= token->args[index].code_arg << shift;
        shift -= 2;
    }
    return (number);
}

int champion_exec_code(t_file *file, int fd)
{
    int index;
    int index2;
    int index3;
    int number;
    int bytes;
    
    index = -1;
    while (file->code[++index].line)
    {
        if (file->code[index].number_byte)
        {
            index2 = check_instruction(file->code[index].instruction);
            ft_putbits_fd((char *)&op_tab[index2].opcode, 1, fd);
            if (op_tab[index2].argument_type_code)
            {
                number = get_argument_type(&file->code[index]);
                ft_putbits_fd((char *)&number, 1, fd);
            }
            index3 = -1;
            while (++index3 < file->code[index].nb_arg)
            {
                bytes = 1;
                if (file->code[index].args[index3].type_arg & T_REG)
                    number = ft_atoi(file->code[index].args[index3].arg + 1);
                else
                {
                    bytes = (op_tab[index2].changes_carry || (file->code[index].args[index3].type_arg & T_IND)) ? 2 : 4;
                    if (file->code[index].args[index3].label_index != -1)
                        number = noname(file, index, file->code[index].args[index3].label_index);
                    else
                    {
                        if (file->code[index].args[index3].type_arg & T_DIR)
                            number = ft_atoi(file->code[index].args[index3].arg + 1);
                        else
                            number = ft_atoi(file->code[index].args[index3].arg);
                    }
                }
                ft_putbits_fd((char *)&number, bytes, fd);
            }
        }
    }
    return (1);
}