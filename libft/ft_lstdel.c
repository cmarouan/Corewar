/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:03:53 by hmney             #+#    #+#             */
/*   Updated: 2018/10/11 12:06:12 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *temp;

	if (alst)
	{
		while (*alst != NULL)
		{
			temp = *alst;
			*alst = (*alst)->next;
			del(temp->content, temp->content_size);
			ft_memdel((void **)&temp);
		}
	}
}
