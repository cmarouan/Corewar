/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statement_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:35:14 by hmney             #+#    #+#             */
/*   Updated: 2019/10/09 20:28:24 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char *check_comment(char *str)
{
	char *new_string;
	char *search_hash;
	char *search_semicolon;	
	char *temp;

	if (!(new_string = ft_strtrim(str)))
		return (NULL);
	if (!*str || str[0] == COMMENT_CHAR || str[0] == ALT_COMMENT_CHAR)
		return (new_string);
	search_hash = ft_strchr(new_string, COMMENT_CHAR);
	search_semicolon = ft_strchr(new_string, ALT_COMMENT_CHAR);
	if (search_semicolon || search_hash)
	{
		search_hash = search_hash ? search_hash : search_semicolon;
		search_semicolon = search_semicolon ? search_semicolon : search_hash;
		search_hash = search_hash < search_semicolon ? search_hash : search_semicolon;
		temp = new_string;
		if (!(new_string = ft_strsub(new_string, 0, search_hash - new_string)))
			return (NULL);
		ft_strdel(&temp);
		temp = new_string;
		if (!(new_string = ft_strtrim(new_string)))
			return (NULL);
		ft_strdel(&temp);
	}
	return (new_string);
}

static t_token *get_token(t_file *file, char *str)
{
	t_token *token;
	int		index;
	int		ret;
	
	if (!(token = (t_token *)ft_memalloc(sizeof(t_token))))
		return (0);
	index = 0;
	if (!(ret = get_label(file, token, str, &index)))
	{
		ft_memdel((void **)&token);
		return (NULL);
	}
	else if (ret == 1)
	{
		if (!(ret = get_instruction(token, str, &index)))
		{
			ft_strdel(&token->label);
			ft_memdel((void **)&token);
			return (NULL);
		}
	}
	if (ret == -1 && !get_args(file, token, str, &index))
	{
		ft_strdel(&token->label);
		ft_strdel(&token->instruction);
		ft_memdel((void **)&token);
		return (NULL);
	}
	return (token);
}

int statement_checker(t_file *file, int *index)
{
	t_list	*new;
	t_token	*token;
	char	*str;

	if (!file->code[*index])
		return (0);
	(*index)--;
    while (file->code[++(*index)])
    {
		if (file->code[*index + 1] == NULL && file->content[ft_strlen(file->content) - 1] != '\n')
			return (0);
		if (!(str = check_comment(file->code[*index])))
            return (0);
        if (!*str || str[0] == COMMENT_CHAR || str[0] == ALT_COMMENT_CHAR)
        {
            ft_strdel(&str);
            continue ;
        }
		if (!(token = get_token(file, str)))
		{
			ft_strdel(&str);
			return (0);
		}
		if(!(new = ft_lstnew((void *)token, sizeof(t_token))))
		{
			ft_strdel(&str);
			ft_memdel((void **)&token);
			return (0);
		}
		ft_lstadd(&file->tokens, new);
		ft_strdel(&str);
	}
	return (1);
}