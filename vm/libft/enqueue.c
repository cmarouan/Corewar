/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enqueue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 10:03:14 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 10:05:42 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	enqueue(t_queue *queue, void *content, size_t content_size)
{
	t_list *elem;

	if (!(elem = ft_lstnew((void *)content, content_size)))
		return (0);
	if (empty_queue(queue))
	{
		queue->front = elem;
		queue->rear = elem;
	}
	else
	{
		queue->rear->next = elem;
		queue->rear = elem;
	}
	queue->counter++;
	return (1);
}
