/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlength.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 00:38:46 by hmney             #+#    #+#             */
/*   Updated: 2018/10/12 00:40:13 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstlength(t_list *begin_list)
{
	t_list	*temp;
	size_t	length;

	length = 0;
	temp = begin_list;
	while (temp != NULL)
	{
		length++;
		temp = temp->next;
	}
	return (length);
}
