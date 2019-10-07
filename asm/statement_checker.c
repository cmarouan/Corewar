/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statement_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:35:14 by hmney             #+#    #+#             */
/*   Updated: 2019/10/07 21:35:47 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int get_label(t_token *token, char *str, int *index)
{
	int index2;

	index2 = *index;
	while (str[*index] && str[*index] != ':' && str[*index] != ' ' && str[*index] != '%')
		(*index)++;
	if (str[*index] == ':')
	{
		if (!(token->label = ft_strsub(str, index2, index)))
			return (0);
		return (1);
	}
	else if (str[*index] == ' ' || str[*index] == '%')
		if (!(token->instruction = ft_strsub(str, index2, index)))
			return (0);
	return (0);
}

int get_instruction(t_token *token, char *str, int *index)
{
	int index2;

	index2 = *index;
	while (str[*index] && str[*index] != ' ' && str[*index] != '%')
		(*index)++;
	if (str[*index])
		return (0);
	if (!(token->instruction = ft_strsub(str, index2, index)))
		return (0);
	return (1);
}

int get_args(t_token *token, char *str, int *index)
{
	char    **args;
	int     length;

	if (!(args = ft_strsplit(str + *index, ',')))
		return (0);
	length = ft_tablen(args);
	if (length == 0 && length > 3)
		return (0);
	if (length >= 1)
		token->arg1 = ft_strtrim(args[0]);
	if (length >= 2)
		token->arg2 = ft_strtrim(args[1]);
	if (length == 3)
		token->arg1 = ft_strtrim(args[2]);
	return (1);
}

t_token *get_token(t_file *file, char *str)
{
	t_token *token;
	t_list  *new;
	char	*temp;
	int		index;
	
	if (!(token = (t_token *)ft_memalloc(sizeof(t_token))))
		return (0);
	index = -1;
	if (get_label(token, str, &index))
		get_instruction(token, str, &index);
	get_args(token, str, &index);
	return (token);
}

int statement_checker(t_file *file, int *index)
{
	t_list *new;
	char *str;

	while (file->code[*index])
	{
		if (!(str = ft_strtrim(file->code[*index])))
			return (0);
		if(!(new = ft_lstnew((void *)get_token(file, str), sizeof(t_token))))
			return (0);
		ft_lstadd(&file->tokens, new);
	}
}