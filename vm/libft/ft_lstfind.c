/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 00:43:34 by hmney             #+#    #+#             */
/*   Updated: 2018/10/12 00:44:58 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_find(t_list *begin_list, void const *content, int (*cmp)())
{
	t_list *temp;

	temp = begin_list;
	while (temp != NULL)
	{
		if ((*cmp)(temp->content, content) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
