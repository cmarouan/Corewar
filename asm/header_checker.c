/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:34:05 by hmney             #+#    #+#             */
/*   Updated: 2019/10/14 23:17:20 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int    check_name_comment_cmd(t_file *file, char *cmd, char *content)
{
    if (!ft_strcmp(cmd, NAME_CMD_STRING) && ft_strlen(content) <= PROG_NAME_LENGTH)
    {
        ft_strcpy(file->header.prog_name, content);
        ft_strdel(&content);
        ft_strdel(&cmd);
        return (NAME_CMD_FLAG);
    }
    if (!ft_strcmp(cmd, COMMENT_CMD_STRING) && ft_strlen(content) <= COMMENT_LENGTH)
    {
        ft_strcpy(file->header.comment, content);
        ft_strdel(&content);
        ft_strdel(&cmd);
        return (COMMENT_CMD_FLAG);
    }
    ft_strdel(&content);
    ft_strdel(&cmd);
    return (0);
}

static char    *get_command(char *str, int *index)
{
    char    *cmd;

    while (str[*index] && !ft_isblank(str[*index]) && str[*index] != '\"')
        (*index)++;
    if (!(cmd = ft_strsub(str, 0, *index)))
        return (NULL);
    return (cmd);
}

static char    *get_content(char *str, int *index, char *cmd)
{
    char    *content;
    int     index2;

    index2 = 0;
    if (str[*index] != '\"')
        return (NULL);
    while (str[++(*index)] && str[*index] != '\"')
        index2++;
    if (str[*index] != '\"' || str[*index + 1] != '\0')
        return (NULL);
    if (!(content = ft_strsub(str, *index - index2, index2)))
        return (NULL);
    return (content);
}

static int get_name_comment_cmd(t_file *file, char *str)
{
    char    *cmd;
    char    *content;
    int     index;

    index = 0;
    if (!(cmd = get_command(str, &index)))
        return (0);
    while (str[index] && ft_isblank(str[index]))
        index++;
    if (!(content = get_content(str, &index, cmd)))
    {
        ft_strdel(&cmd);
        return (0);
    }
    return (check_name_comment_cmd(file, cmd, content));
}

int header_checker(t_file *file, int *index)
{
    char    *str;
    int     flag;
    int     ret;

    flag = 0;
    while (file->code[++(*index)].line)
    {
        if (!(str = ft_strtrim(file->code[*index].line)))
            return (0);
        if (!*str || str[0] == COMMENT_CHAR || str[0] == ALT_COMMENT_CHAR)
        {
            ft_strdel(&str);
            continue ;
        }
        if (!(ret = get_name_comment_cmd(file, str)) || (flag & ret))
        {
            ft_strdel(&str);
            return ((flag != 3 || (flag & ret)) ? 0 : 1);
        }
        flag |= ret;
        ft_strdel(&str);
    }
    return (1);
}
