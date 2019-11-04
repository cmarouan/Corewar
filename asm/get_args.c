/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:56:32 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 14:10:16 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			get_args(t_file *file, t_token *token, char *str, int *index)
{
	char	**args;
	char	*arg;
	int		index2;
	int		index3;

	if (!(args = ft_strsplit(str + *index, SEPARATOR_CHAR)))
		return (0);
	if (!check_args2(token, args, str + *index))
	{
		free_tab(&args);
		return (0);
	}
	index3 = -1;
	while (++index3 < token->nb_arg)
	{
		if (!(arg = ft_strtrim(args[index3])) ||
				!check_args(file, token, arg, index3))
		{
			free_tab(&args);
			return (0);
		}
		token->args[index3].arg = arg;
	}
	free_tab(&args);
	return (1);
}
