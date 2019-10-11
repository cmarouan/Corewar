/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 00:40:57 by hmney             #+#    #+#             */
/*   Updated: 2018/10/12 00:41:49 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **begin_list)
{
	t_list *temp;

	while (*begin_list != NULL)
	{
		temp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(temp);
	}
}
