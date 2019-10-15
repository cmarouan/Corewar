/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:58:49 by hmney             #+#    #+#             */
/*   Updated: 2019/10/15 12:01:28 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*check_comment(char *str)
{
	char *new_str;
	char *s_hash;
	char *s_semicolon;
	char *temp;

	if (!(new_str = ft_strtrim(str)))
		return (NULL);
	s_hash = ft_strchr(new_str, COMMENT_CHAR);
	s_semicolon = ft_strchr(new_str, ALT_COMMENT_CHAR);
	if (!*new_str || new_str[0] == COMMENT_CHAR ||
			new_str[0] == ALT_COMMENT_CHAR || (!s_semicolon && !s_hash))
		return (new_str);
	s_hash = s_hash ? s_hash : s_semicolon;
	s_semicolon = s_semicolon ? s_semicolon : s_hash;
	s_hash = s_hash < s_semicolon ? s_hash : s_semicolon;
	temp = new_str;
	if (!(new_str = ft_strsub(new_str, 0, s_hash - new_str)))
		return (NULL);
	ft_strdel(&temp);
	temp = new_str;
	if (!(new_str = ft_strtrim(new_str)))
		return (NULL);
	ft_strdel(&temp);
	return (new_str);
}
